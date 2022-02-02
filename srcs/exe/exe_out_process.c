/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_out_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 17:59:16 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/02 14:27:31 by buschiix         ###   ########.fr       */
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
#include "error.h"

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

void	exe_out_process(t_command *cmd, t_data *data)
{
	cmd->pid = fork();
	if (!cmd->pid)
		_son(cmd->args, data);
	signal_ignore();
//	waitpid(cmd->pid, &g_last_return, 0);
//	signal_current();
//	if (WIFSIGNALED(g_last_return))
//		g_last_return = WTERMSIG(g_last_return) + 128;
//	else
//		g_last_return = WEXITSTATUS(g_last_return);
}
