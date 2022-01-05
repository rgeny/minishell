/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_out_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 17:59:16 by rgeny             #+#    #+#             */
/*   Updated: 2022/01/05 21:09:38 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include "env.h"
#include "global.h"
#include "str.h"
#include "parsing.h"

int	exe_out_process(char **cmd, t_env *env)
{
	pid_t	pid;
	int		ret;
	char	**env_cpy;

	pid = fork();
	if (!pid)
	{
		env_cpy = env_switch(&env, 0);
		glo_pwd(0, 1);
		parsing_path(cmd, env);
		execve(cmd[0], cmd, env_cpy);
		str_free_string(cmd);
		str_free_string(env_cpy);
		env_del_all(env);
		exit(127);
	}
	waitpid(pid, &ret, 0);
	return (WEXITSTATUS(ret));
}
