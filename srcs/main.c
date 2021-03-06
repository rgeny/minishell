/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 18:44:54 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/13 18:32:34 by rgeny            ###   ########.fr       */
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
#include "common.h"

int	g_last_return;

static void	_init(char *envp[], t_data *data, char *argv[])
{
	int	i;

	data->is_verbose_mod = false;
	i = 1;
	while (argv[i])
	{
		if (!str_cmp(argv[i], "-v") || !str_cmp(argv[i], "--verbose"))
			data->is_verbose_mod = true;
		i++;
	}
	g_last_return = 0;
	data->env = 0;
	env_init(&data->env, envp);
	data->pwd = 0;
	data->ast = NULL;
	data->pipefd[0] = STDIN_FILENO;
	data->pipefd[1] = STDOUT_FILENO;
	data->fd_in = STDIN_FILENO;
	data->pwd = str_dup(env_find_val(data->env, ENV_PWD));
	uti_interactive(INTERACTIVE_INIT);
}

static void	_exe(t_data *data)
{
	char	*rl;

	rl = exe_readline();
	while (rl)
	{
		error_reset();
		if (parser_main(data, rl) == SUCCESS && data->ast)
			exe_main(data->ast, data);
		free_ast(&data->ast);
		rl = exe_readline();
	}
}

int	main(__attribute((unused)) int argc,
	__attribute__((unused)) char *argv[], char *envp[])
{
	t_data	data;

	signal_current();
	_init(envp, &data, argv);
	_exe(&data);
	if (uti_interactive(INTERACTIVE_RETURN_IS_IT))
		str_print_fd("exit\n", STDOUT_FILENO);
	clean_all(&data);
	return (g_last_return);
}
