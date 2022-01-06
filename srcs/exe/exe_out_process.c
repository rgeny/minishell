/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_out_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 17:59:16 by rgeny             #+#    #+#             */
/*   Updated: 2022/01/06 23:20:33 by buschiix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include "env.h"
#include "str.h"
#include "parsing.h"
#include "print.h"

void	exe_out_process(char **cmd, t_data *data)
{
	pid_t	pid;
	char	**env_cpy;

	pid = fork();
	if (!pid)
	{
		env_cpy = env_switch(data, 0);
		free(data->pwd);
		parsing_path(cmd, data->env);
		execve(cmd[0], cmd, env_cpy);
		print_error(cmd[0], ": command not found\n", 0, data);
		str_free_string(cmd);
		str_free_string(env_cpy);
		env_del_all(data->env);
		exit(127);
	}
	waitpid(pid, &data->ret, 0);
	data->ret = WEXITSTATUS(data->ret);
}
