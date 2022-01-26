/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 18:44:54 by rgeny             #+#    #+#             */
/*   Updated: 2022/01/26 18:04:03 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <readline/history.h>
#include "env.h"
#include "expander.h"
#include "exe.h"
#include "lexer.h"
#include "parser.h"
#include "minishell_signal.h"
#include "cleaner.h"

static void	_init(char *envp[], t_data *data)
{
	t_env	*pwd;

	data->env = 0;
	env_init(&data->env, envp);
	data->ret = 0;
	data->pwd = 0;
	data->tokens = NULL;
	pwd = env_find(data->env, "PWD");
	if (pwd)
		data->pwd = str_dup(pwd->value);
	data->interactive.line = 0;
	if (!isatty(0) || !isatty(1) || !isatty(2))
		data->interactive.is_interactive = 0;
	else
		data->interactive.is_interactive = 1;
}

static void	_exe(t_data *data)
{
	char	*rl;
	char	**cmd;
	int		i;
	int		in;
	int		heredoc;
	char	*tmp;

	rl = exe_readline(data);
	while (rl)
	{
		data->tokens = lexer_lex(rl);
		// lexer_print_tokens(data->tokens);

		if (data->tokens && parse_tokens(data, data->tokens) == 0)
		{
			add_history(rl);
			// TODO : move expander inside command (ast leaves)
			tmp = expander_asterisk(rl);
			if (tmp)
			{
				free(rl);
				rl = tmp;
			}

			cmd = str_split(rl, " ");
			str_free(rl);
			if (cmd && cmd[0] && !str_cmp("<<", cmd[0]))
			{
				heredoc = exe_heredoc(cmd[1], data);
				if (heredoc == -1)
				{
					str_free_list(cmd);
					cmd = 0;
				}
				else
				{
					in = dup(0);
					dup2(heredoc, 0);
					i = 2;
				}
			}
			else
			{
				heredoc = -1;
				in = -1;
				i = 0;
			}
			if (cmd && cmd[i])
			{
				expander_var(&cmd[i], data);
				env_new_(cmd[i], &data->env);
				lexer_free_tokens(&data->tokens);
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
			lexer_free_tokens(&data->tokens);
			str_free_list(cmd);
		}
		else // Something went wrong during parsing
		{
			lexer_free_tokens(&data->tokens);
			str_free(rl);
		}
		rl = exe_readline(data);

	}
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
	_init(envp, &data);
	_exe(&data);
	if (data.interactive.is_interactive)
		write(1, "exit\n", 5);
	clean_all(&data);
	return (data.ret);
}
