/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 18:44:54 by rgeny             #+#    #+#             */
/*   Updated: 2022/01/04 23:08:01 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include <readline/history.h>
#include <fcntl.h>
#include "builtin.h"
#include "env.h"
#include "utils.h"
#include "str.h"
#include "global.h"
#include "expander.h"
#include "exe.h"

static void	static_init(char *envp[], t_env **env)
{
	int		fd;
	t_env	*pwd;

	if (!isatty(0) || !isatty(1) || !isatty(2))
	{
		fd = open("/dev/null", O_WRONLY);
		dup2(fd, 2);
		close(fd);
	}
	*env = 0;
	env_init(env, envp);
	pwd = env_find(*env, "PWD");
	if (pwd)
		glo_pwd(str_ndup(pwd->value, str_len(pwd->value, 0)), 0);
}

static int	static_exe(t_env **env)
{
	char	*rl;
	char	**cmd;
	int		ret;

	ret = 0;
	rl = uti_readline(*env);
	while (rl)
	{
		cmd = str_split(rl, " ");
		if (cmd[0])
		{
			add_history(rl);
			expander_env(cmd, *env);
			env_new_(cmd[0], env);
			ret = exe_builtin(cmd, env);
			if (ret == -1)
				ret = exe_out_process(cmd, *env);
		}
		free(rl);
		str_free_string(cmd);
		rl = uti_readline(*env);
	}
	return (ret);
}

static void	static_free(t_env *env)
{
	glo_pwd(0, 1);
	env_del_all(env);
}

int	main(int ret, __attribute__((unused)) char *argv[], char *envp[])
{
	t_env	*env;

	static_init(envp, &env);
	ret = static_exe(&env);
	static_free(env);
	return (ret);
}
