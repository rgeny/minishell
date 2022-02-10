/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 10:08:26 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/10 11:09:18 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
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

	exe_redir(ast->cmd, ast->cmd->redirections, ast->cmd->fd_heredoc, data);
	if (!is_error())
	{
		expand_args(ast->cmd, ast->cmd->cargs, data);
		args = lst_switch(ast->cmd->cargs, ast->cmd->arg_nb);
	}
	if (!is_error() && ast->cmd->arg_nb && args[0])
	{
		exe_builtin(args, &args[1], data);
		if (g_last_return == -1)
			exe_out_process(ast->cmd, args, data);
		str_free_list(args);
	}
	if (is_error())
		g_last_return = error_get();
	error_reset();
}
