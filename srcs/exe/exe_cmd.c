/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 10:08:26 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/10 14:55:21 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"
#include <stdio.h>
#include "error.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "str.h"

void	_print(char **s)
{
	while (*s)
	{
		printf("%s\n", *s);
		s++;
	}
}

void	exe_cmd(t_ast *ast, t_data *data)
{
	char	**args;
	int		arg_n;

	arg_n = 0;
	exe_redir(ast->cmd, ast->cmd->redirections, ast->cmd->fd_heredoc, data);
	if (!is_error())
	{
		expand_args(ast->cmd, ast->cmd->cargs, data, &arg_n);
		args = lst_switch(ast->cmd->cargs, arg_n);
	}
	if (!is_error() && arg_n && args[0])
	{
		exe_builtin(args, &args[1], data);
		if (g_last_return == -1)
			exe_out_process(ast->cmd, args, data);
		str_free_list(&args);
	}
	if (is_error())
		g_last_return = error_get();
	ast->cmd->last_return = g_last_return;
	error_reset();
}
