/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 18:44:54 by rgeny             #+#    #+#             */
/*   Updated: 2022/01/06 11:20:14 by tokino           ###   ########.fr       */
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
#include "lexer.h"

#include <dirent.h>

static void	static_init(char *envp[], t_env **env, char *exe)
{
	t_env	*pwd;

	*env = 0;
	env_init(env, envp, exe);
	pwd = env_find(*env, "PWD");
	if (pwd)
		glo_pwd(str_ndup(pwd->value, str_len(pwd->value, 0)), 0);
}

static int	static_exe(t_env **env)
{
	char	*rl;
	char	**cmd;
	int		ret;
	t_token	*tokens;

	ret = 0;
	tokens = NULL;
	rl = uti_readline(*env);
	while (rl)
	{
		// tokens = lexer_lex(rl);
		// lexer_print_tokens(tokens);
		cmd = str_split(rl, " ");
		if (cmd[0])
		{
			add_history(rl);
			expander_env(cmd, *env);
			env_new_(cmd[0], env);
			lexer_free_tokens(&tokens);
			ret = exe_builtin(cmd, env);
			if (ret == -1)
				ret = exe_out_process(cmd, *env);
		}
		lexer_free_tokens(&tokens);
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

	static_init(envp, &env, argv[0]);
	ret = static_exe(&env);
	static_free(env);
	return (ret);
}
