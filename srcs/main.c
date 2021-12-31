/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 18:44:54 by rgeny             #+#    #+#             */
/*   Updated: 2021/12/31 17:47:43 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "builtin.h"
#include "env.h"
#include "utils.h"
#include "str.h"

static int	static_exec_in_process(char **cmd, int *ret, t_env **env)
{
	if (!str_cmp(cmd[0], "export"))
		*ret = builtin_export(cmd, env);
	else if (!str_cmp(cmd[0], "unset"))
		*ret = builtin_unset(cmd, env);
	else
		return (1);
	return (0);
}

static int	static_exec_out_process(char **cmd, t_env *env)
{
	pid_t	pid;
	int		ret;
	char	**env_cpy;

	pid = fork();
	if (!pid)
	{
		env_cpy = env_switch(env, 0);
		if (!str_cmp(cmd[0], "env"))
		{
			free(cmd[0]);
			cmd[0] = str_join(BUILTIN_PATH, "env", '/');
			execve(cmd[0], cmd, env_cpy);
		}
		else
			execve(cmd[0], cmd, env_cpy);
		str_free_string(cmd);
		str_free_string(env_cpy);
		env_del_all(env);
		exit (127);
	}
	waitpid(pid, &ret, 0);
	return (WEXITSTATUS(ret));
}

int	main(int argc, char *argv[], char *envp[])
{
	t_env	*env;
	char	*s;
	char	**cmd;
	int		ret;

	env = 0;
	env_init(&env, envp, argv[0]);
	s = readline("$>");
	while (str_cmp(s, "exit") && argc)
	{
		cmd = str_split(s, " ");
		if (cmd[0])
		{
			printf("\n");
			add_history(s);
			env_new_(cmd[0], &env);
			if (static_exec_in_process(cmd, &ret, &env))
				ret = static_exec_out_process(cmd, env);
			printf("\n");
			env_print_one(env_find(env, "_"));
			printf("return value : %d\n\n", ret);
		}
		str_free_string(cmd);
		free(s);
		s = readline("$>");
	}
	free(s);
	env_del_all(env);
}
