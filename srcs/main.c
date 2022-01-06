/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 18:44:54 by rgeny             #+#    #+#             */
/*   Updated: 2022/01/06 17:44:24 by buschiix         ###   ########.fr       */
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

static void	static_init(char *envp[], t_data *data, char *exe)
{
	t_env	*pwd;

	data->env = 0;
	env_init(&data->env, envp, exe);
	pwd = env_find(data->env, "PWD");
	if (pwd)
		glo_pwd(str_ndup(pwd->value, str_len(pwd->value, 0)), 0);
}

static int	static_exe(t_data *data)
{
	char	*rl;
	char	**cmd;
	int		ret;
	t_token	*tokens;

	ret = 0;
	tokens = NULL;
	rl = uti_readline(data);
	while (rl)
	{
		// tokens = lexer_lex(rl);
		// lexer_print_tokens(tokens);
		cmd = str_split(rl, " ");
		if (cmd[0])
		{
			add_history(rl);
			expander_env(cmd, data->env);
			env_new_(cmd[0], &data->env);
			lexer_free_tokens(&tokens);
			ret = exe_builtin(cmd, data);
			if (ret == -1)
				ret = exe_out_process(cmd, data->env);
		}
		lexer_free_tokens(&tokens);
		free(rl);
		str_free_string(cmd);
		rl = uti_readline(data);
	}
	return (ret);
}

static void	static_free(t_data data)
{
	glo_pwd(0, 1);
	env_del_all(data.env);
}

int	main(int ret, __attribute__((unused)) char *argv[], char *envp[])
{
	t_data	data;

	static_init(envp, &data, argv[0]);
	ret = static_exe(&data);
	static_free(data);
	return (ret);
}
