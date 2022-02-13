/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_subshell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 03:48:59 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/13 12:01:27 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

static void	_son(t_ast *ast, t_data *data)
{
	dup_and_close(&data->pipefd[0], STDIN_FILENO);
	dup_and_close(&data->pipefd[1], STDOUT_FILENO);
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
	close_fd(&data->pipefd[0], STDIN_FILENO);
	close_fd(&data->pipefd[1], STDOUT_FILENO);
}
