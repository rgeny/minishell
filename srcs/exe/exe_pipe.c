/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 09:48:32 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/13 11:17:30 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

static void	_loop_exe_pipe(t_ast *ast, t_data *data)
{
	int	fd_tmp;

	if (ast->is_subshell)
		exe_subshell(ast, data);
	else if (ast->type == E_NODE_TYPE_COMMAND)
		exe_cmd(ast, data);
	else
	{
		_loop_exe_pipe(ast->left, data);
		pipe(data->pipefd);
		fd_tmp = data->pipefd[0];
		data->pipefd[0] = data->fd_in;
		data->fd_in = fd_tmp;
		_loop_exe_pipe(ast->right, data);
	}
}

void	exe_pipe(t_ast *ast, t_data *data)
{
	pipe(data->pipefd);
	data->fd_in = data->pipefd[0];
	data->pipefd[0] = STDIN_FILENO;
	_loop_exe_pipe(ast->left, data);
	data->pipefd[0] = data->fd_in;
	_loop_exe_pipe(ast->right, data);
}
