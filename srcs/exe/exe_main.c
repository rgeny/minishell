/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 14:14:36 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/09 12:28:55 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/wait.h>
#include <error.h>
#include "struct.h"
#include "exe.h"
#include "minishell_signal.h"

static void	_wait_all(t_ast *ast, t_data *data)
{
	if (!ast)
		return ;
	if (ast->type == E_NODE_TYPE_COMMAND)
	{
		if (ast->cmd->pid && waitpid(ast->cmd->pid, &g_last_return, 0) != -1)
		{
			if (WIFSIGNALED(g_last_return))
				g_last_return = WTERMSIG(g_last_return) + 128;
			else
				g_last_return = WEXITSTATUS(g_last_return);
		}
	}
	_wait_all(ast->left, data);
	_wait_all(ast->right, data);
}

void	exe_main(t_ast *ast, t_data *data)
{
	if (ast->type == E_NODE_TYPE_PIPE)
		exe_pipe(ast, data);
	else if (ast->type == E_NODE_TYPE_COMMAND)
		exe_cmd(ast, data);
	else if (ast->type == E_NODE_TYPE_AND)
	{
		exe_main(ast->left, data);
		if (g_last_return == SUCCESS)
			exe_main(ast->right, data);
	}
	else if (ast->type == E_NODE_TYPE_OR)
	{
		exe_main(ast->left, data);
		if (g_last_return != SUCCESS)
			exe_main(ast->right, data);
	}
	_wait_all(ast, data);
	signal_current();
}
