/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 18:44:54 by rgeny             #+#    #+#             */
/*   Updated: 2022/01/04 17:13:05 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <readline/history.h>
#include <string.h>
#include <fcntl.h>
#include "builtin.h"
#include "env.h"
#include "utils.h"
#include "str.h"
#include "global.h"
#include "expander.h"

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

static void	static_pathing(char **cmd, t_env *env)
{
	int		i;
	char	**split;
	char	*s;

	if (!access(cmd[0], F_OK | X_OK))
		return ;
	env = env_find(env, "PATH");
	if (!env)
		return ;
	split = str_split(env->value, ":");
	i = 0;
	while (split[i])
	{
		s = str_join(split[i], cmd[0], '/');
		if (!access(s, F_OK | X_OK))
		{
			free(cmd[0]);
			cmd[0] = s;
			str_free_string(split);
			return ;
		}
		free(s);
		i++;
	}
	str_free_string(split);
}

static int	static_exec_out_process(char **cmd, t_env *env)
{
	pid_t	pid;
	int		ret;
	char	**env_cpy;

	pid = fork();
	if (!pid)
	{
		env_cpy = env_switch(&env, 0);
		glo_pwd(0, 1);
		static_pathing(cmd, env);
		execve(cmd[0], cmd, env_cpy);
		str_free_string(cmd);
		str_free_string(env_cpy);
		env_del_all(env);
		exit (127);
	}
	waitpid(pid, &ret, 0);
	return (WEXITSTATUS(ret));
}

static void	static_fd(void)
{
	int	fd;

	if (!isatty(0) || !isatty(1) || !isatty(2))
	{
		fd = open("/dev/null", O_WRONLY);
		dup2(fd, 2);
		close(fd);
	}
}

int	main(int ret, char **cmd, char *envp[])
{
	t_env	*env;
	t_env	*tmp;
	char	*s;

	env = 0;
	static_fd();
	env_init(&env, envp);
	tmp = env_find(env, "PWD");
	if (tmp)
		glo_pwd(str_ndup(tmp->value, str_len(tmp->value, 0)), 0);
	s = uti_readline(env);
	while (s)
	{
		cmd = str_split(s, " ");
		if (cmd[0])
		{
			expander_env(cmd, env);
			add_history(s);
			free(s);
			env_new_(cmd[0], &env);
			if (static_exec_in_process(cmd, &ret, &env))
				ret = static_exec_out_process(cmd, env);
		}
		else
			free(s);
		str_free_string(cmd);
		s = uti_readline(env);
	}
	free(s);
	glo_pwd(0, 1);
	env_del_all(env);
	return (ret);
}
