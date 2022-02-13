/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 14:14:36 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/13 18:00:48 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

static void	_take_return_value(void)
{
	if (WIFSIGNALED(g_last_return))
	{
		if (WTERMSIG(g_last_return) == SIGQUIT)
			str_print_fd_nl("Quit (core dumped)", STDOUT_FILENO);
		else if (WTERMSIG(g_last_return) == SIGINT)
			str_print_fd("\n", STDOUT_FILENO);
		g_last_return = WTERMSIG(g_last_return) + SIG_ERROR;
	}
	else
		g_last_return = WEXITSTATUS(g_last_return);
}

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
		_take_return_value();
	else if (ast->type == E_NODE_TYPE_COMMAND)
		g_last_return = ast->cmd->last_return;
	if (ast->pid == 0)
	{
		_wait_process(ast->left, data);
		_wait_process(ast->right, data);
	}
	signal_current();
}

static void	_exe_and(t_ast *ast, t_data *data)
{
	exe_main(ast->left, data);
	if (g_last_return == SUCCESS)
		exe_main(ast->right, data);
}

static void	_exe_or(t_ast *ast, t_data *data)
{
	exe_main(ast->left, data);
	if (g_last_return != SUCCESS)
		exe_main(ast->right, data);
}

void	exe_main(t_ast *ast, t_data *data)
{
	if (ast->is_subshell)
	{
		exe_subshell(ast, data);
		_wait_process(ast, data);
	}
	else if (ast->type == E_NODE_TYPE_PIPE)
	{
		exe_pipe(ast, data);
		_wait_process(ast, data);
	}
	else if (ast->type == E_NODE_TYPE_COMMAND)
	{
		exe_cmd(ast, data);
		_wait_process(ast, data);
	}
	else if (ast->type == E_NODE_TYPE_AND)
		_exe_and(ast, data);
	else if (ast->type == E_NODE_TYPE_OR)
		_exe_or(ast, data);
}
