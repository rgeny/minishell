/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 18:44:54 by rgeny             #+#    #+#             */
/*   Updated: 2022/01/09 13:23:26 by buschiix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <readline/history.h>
#include "env.h"
#include "expander.h"
#include "exe.h"
#include "lexer.h"
#include "minishell_signal.h"

static void	static_init(char *envp[], t_data *data)
{
	t_env	*pwd;

	data->env = 0;
	env_init(&data->env, envp);
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
	int		i;
	int		in;
	int		heredoc;

	tokens = NULL;
	rl = exe_readline(data);
	while (rl)
	{
		// tokens = lexer_lex(rl);
		// lexer_print_tokens(tokens);
		cmd = str_split(rl, " ");
		if (!str_cmp("<<", cmd[0]))
		{
			heredoc = exe_heredoc(cmd[1]);
			in = dup(0);
			dup2(heredoc, 0);
			i = 2;
		}
		else
		{
			heredoc = -1;
			in = -1;
			i = 0;
		}
		if (cmd && cmd[i])
		{
			add_history(rl);
			expander_cmd(&cmd[i], data);
			env_new_(cmd[i], &data->env);
			lexer_free_tokens(&tokens);
			exe_builtin(&cmd[i], data);
			if (data->ret == -1)
				exe_out_process(&cmd[i], data);
		}
		if (heredoc >= 0)
		{
			dup2(in, 0);
			close(in);
			close(heredoc);
		}
		lexer_free_tokens(&tokens);
		str_free(rl);
		str_free_list(cmd);
		rl = exe_readline(data);
	}
}

static void	static_free(t_data data)
{
	str_free(data.pwd);
	env_del_all(data.env);
}

//#include <stdio.h>
//#include <stdlib.h>
//#include <sys/time.h>
//#include <sys/resource.h>

int	main(__attribute((unused)) int argc,
	__attribute__((unused)) char *argv[], char *envp[])
{
//	struct rlimit	l;
	t_data	data;

//	getrlimit(RLIMIT_MEMLOCK, &l);
//	l.rlim_cur = 1;
//	setrlimit(RLIMIT_MEMLOCK, &l);

	signal_current(&data);
	static_init(envp, &data);
	static_exe(&data);
	if (data.interactive.is_interactive)
		write(1, "exit\n", 5);
	static_free(data);
	return (data.ret);
}
