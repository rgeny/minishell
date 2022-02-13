/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_subshell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 03:48:59 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/13 11:30:37 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

static void	_son(t_ast *ast, t_data *data)
{
	exe_main(ast, data);
	env_del_all(data->env);
	free_ast(&data->ast);
	str_free(&data->pwd);
	exit(g_last_return);
}

void	exe_subshell(t_ast *ast, t_data *data)
{
	ast->is_subshell = false;
	ast->pid = fork();
	if (ast->pid == -1)
		error_print(FORK_ERROR, NULL, NULL, ERROR_EXEC);
	else if (ast->pid == 0)
		_son(ast, data);
	else
	{
		waitpid(ast->pid, &g_last_return, 0);
		if (WIFSIGNALED(g_last_return))
			g_last_return = WTERMSIG(g_last_return) + SIG_ERROR;
		else
			g_last_return = WEXITSTATUS(g_last_return);
	}
}
