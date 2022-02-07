/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 18:44:54 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/07 16:08:34 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <readline/history.h>
#include "error.h"
#include "env.h"
#include "expander.h"
#include "exe.h"
#include "lexer.h"
#include "parser.h"
#include "minishell_signal.h"
#include "cleaner.h"
#include "utils.h"

int	g_last_return;
static void	_init(char *envp[], t_data *data)
{
	g_last_return = 0;
	data->env = 0;
	env_init(&data->env, envp);
	data->pwd = 0;
	data->ast_root = NULL;
	data->pipefd[0] = STDIN_FILENO;
	data->pipefd[1] = STDOUT_FILENO;
	data->pwd = str_dup(env_find_val(data->env, ENV_PWD));
	uti_interactive(INTERACTIVE_INIT);
}

static void	_exe(t_data *data)
{
	char	*rl;
	int		in;
	int		out;

	rl = exe_readline(data);
	while (rl && str_cmp(rl, "exit"))
	{
		error_reset();
		add_history(rl);
		if (parser_main(data, rl) == SUCCESS && data->ast_root)
		{
			// expander_main(data, data->ast_root);
			in = dup(0);
			out = dup(1);
			// exe_main(data->ast_root, data);
			dup2(in, 0);
			dup2(out, 1);
			close(in);
			close(out);
		}
		str_free(rl);
		free_ast(&data->ast_root);
		rl = exe_readline(data);
	}
}

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>

int	main(__attribute((unused)) int argc,
	__attribute__((unused)) char *argv[], char *envp[])
{
	struct rlimit	l;
	getrlimit(RLIMIT_AS, &l);
	l.rlim_cur = 160300000;
	setrlimit(RLIMIT_AS, &l);

	t_data	data;
	signal_current();
	_init(envp, &data);
	_exe(&data);
	if (uti_interactive(INTERACTIVE_RETURN_IS_IT))
		write(1, "exit\n", 5);
	clean_all(&data);
	return (g_last_return);
}
