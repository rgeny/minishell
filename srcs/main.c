/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 18:44:54 by rgeny             #+#    #+#             */
/*   Updated: 2022/01/01 11:15:02 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <readline/history.h>
#include <string.h>
#include "builtin.h"
#include "env.h"
#include "utils.h"
#include "str.h"
#include "global.h"

char	*g_path = 0;

static void	static_init_path(void)
{
	char	tmp[PATH_CHAR_MAX + 1];

	getcwd(tmp, PATH_CHAR_MAX + 1);
	g_path = str_join(tmp, "builtin", '/');
}

static int	static_exec_in_process(char **cmd, int *ret, t_env **env)
{
	if (!str_cmp(cmd[0], "export"))
		*ret = builtin_export(cmd, env);
	else if (!str_cmp(cmd[0], "unset"))
		*ret = builtin_unset(cmd, env);
	else if (!str_cmp(cmd[0], "exit"))
		*ret = builtin_exit(cmd, *env);
	else if (!str_cmp(cmd[0], "cd"))
		*ret = builtin_cd(cmd, *env);
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
		glo_pwd(0, 1);
		env_cpy = env_switch(&env, 0);
		if (!str_cmp(cmd[0], "env"))
		{
			free(cmd[0]);
			cmd[0] = str_join(g_path, "env", '/');
			execve(cmd[0], cmd, env_cpy);
		}
		else if (!str_cmp(cmd[0], "echo"))
		{
			free(cmd[0]);
			cmd[0] = str_join(g_path, "echo", '/');
			execve(cmd[0], cmd, env_cpy);
		}
		else if (!str_cmp(cmd[0], "pwd"))
		{
			free(cmd[0]);
			cmd[0] = str_join(g_path, "pwd", '/');
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

int	main(int ret, char **cmd, char *envp[])
{
	t_env	*env;
	t_env	*tmp;
	char	*s;

	env = 0;
	env_init(&env, envp);
	tmp = env_find(env, "PWD");
	if (tmp)
		glo_pwd(str_ndup(tmp->value, str_len(tmp->value, 0)), 0);
	static_init_path();
	s = uti_readline(env);
	while (1)
	{
		cmd = str_split(s, " ");
		if (cmd[0])
		{
			add_history(s);
			free(s);
			env_new_(cmd[0], &env);
			if (static_exec_in_process(cmd, &ret, &env))
				ret = static_exec_out_process(cmd, env);
			printf("\n");
			printf("glo : %s\n", glo_pwd(0, 0));
			env_print_one(env_find(env, "_"));
			printf("return value : %d\n\n", ret);
		}
		else
			free(s);
		str_free_string(cmd);
		s = uti_readline(env);
	}
	free(s);
	glo_pwd(0, 1);
	env_del_all(env);
}
