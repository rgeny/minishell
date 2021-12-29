/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 18:44:54 by rgeny             #+#    #+#             */
/*   Updated: 2021/12/29 22:56:15 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "env.h"
#include "utils.h"
#include "str.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_env	*env;
	char	*s;
	char	**cmd;
	char	**env_cpy;
	pid_t	pid;

	env = 0;
	env_init(&env, envp, argv[0]);
	s = readline("$>");
	while (s)
	{
		add_history(s);
		cmd = str_split(s, " =");
		free(s);
		pid = fork();
		if (!pid)
		{
			if (!str_cmp(cmd[0], "export"))
				exit(env_export(cmd, &env));
			else if (!str_cmp(cmd[0], "env"))
				env_print_all(env);
			else
			{
				env_cpy = env_switch(env, 0);
				execve(cmd[0], cmd, env_cpy);
			}
			exit(127);
		}
		wait(0);
		s = readline("$>");
	}
	env_del_all(env);
}
