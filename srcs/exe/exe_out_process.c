/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_out_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 17:59:16 by rgeny             #+#    #+#             */
/*   Updated: 2022/01/29 12:43:13 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include "env.h"
#include "str.h"
#include "print.h"
#include "minishell_signal.h"
#include "expander.h"

static void	_son(char **cmd, t_data *data)
{
	char	**env_cpy;
	char	*path;

	signal_fork();
	env_cpy = env_switch(data, 0);
	str_free(data->pwd);
	path = expander_path(cmd[0], data->env);
	execve(path, cmd, env_cpy);
	print_error(cmd[0], ": command not found\n", 0, data);
	str_free_list(cmd);
	str_free_list(env_cpy);
	str_free(path);
	env_del_all(data->env);
	exit(127);
}

void	exe_out_process(char **cmd, t_data *data)
{
	pid_t	pid;

	pid = fork();
	if (!pid)
		_son(cmd, data);
	signal_ignore();
	waitpid(pid, &data->ret, 0);
	signal_current(0);
	if (WIFSIGNALED(data->ret))
		data->ret = WTERMSIG(data->ret) + 128;
	else
		data->ret = WEXITSTATUS(data->ret);
}
