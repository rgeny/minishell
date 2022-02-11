/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 14:14:36 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/11 21:07:19 by buschiix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

static void	_wait_process(t_ast *ast, t_data *data)
{
	pid_t	pid;

	if (!ast)
		return ;
	pid = 0;
	if (ast->pid != 0)
		pid = ast->pid;
	else if (ast->type == E_NODE_TYPE_COMMAND)
		pid = ast->cmd->pid;
	if (pid != 0 && waitpid(pid, &g_last_return, 0) != -1)
	{
		if (WIFSIGNALED(g_last_return))
			g_last_return = WTERMSIG(g_last_return) + SIG_ERROR;
		else
			g_last_return = WEXITSTATUS(g_last_return);
	}
	else if (ast->type == E_NODE_TYPE_COMMAND)
		g_last_return = ast->cmd->last_return;
	_wait_process(ast->left, data);
	_wait_process(ast->right, data);
}

void	exe_main(t_ast *ast, t_data *data)
{
	if (ast->is_subshell)
	{
		ast->is_subshell = false;
		ast->pid = fork();
		if (ast->pid == 0)
			exe_subshell(ast, data);
	}
	else if (ast->type == E_NODE_TYPE_PIPE)
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
	_wait_process(ast, data);
	signal_current();
}
