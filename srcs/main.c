/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 18:44:54 by rgeny             #+#    #+#             */
/*   Updated: 2022/01/06 20:30:02 by buschiix         ###   ########.fr       */
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
#include "expander.h"
#include "exe.h"
#include "lexer.h"

#include <dirent.h>

static void	static_init(char *envp[], t_data *data, char *exe)
{
	t_env	*pwd;

	data->env = 0;
	env_init(&data->env, envp, exe);
	data->ret = 0;
	data->pwd = 0;
	pwd = env_find(data->env, "PWD");
	if (pwd)
		data->pwd = str_ndup(pwd->value, str_len(pwd->value, 0));
	data->interactive.line = 0;
	if (!isatty(0) || !isatty(1) || !isatty(2))
		data->interactive.is_interactive = 0;
	else
		data->interactive.is_interactive = 1;
}

static void	static_exe(t_data *data)
{
	char	*rl;
	char	**cmd;
	t_token	*tokens;

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
			exe_builtin(cmd, data);
			if (data->ret == -1)
				exe_out_process(cmd, data);
		}
		lexer_free_tokens(&tokens);
		free(rl);
		str_free_string(cmd);
		rl = uti_readline(data);
	}
}

static void	static_free(t_data data)
{
	free(data.pwd);
	env_del_all(data.env);
}

int	main(__attribute((unused)) int argc, __attribute__((unused)) char *argv[], char *envp[])
{
	t_data	data;

	static_init(envp, &data, argv[0]);
	static_exe(&data);
	static_free(data);
	return (data.ret);
}
