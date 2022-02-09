/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 09:48:32 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/09 12:29:23 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "struct.h"
#include "exe.h"

static void	_dup_and_close(int oldfd, int newfd)
{
	dup2(oldfd, newfd);
	close(oldfd);
}

static void	_pipe_stdin(int pipefd[2])
{
	pipe(pipefd);
	_dup_and_close(pipefd[1], STDOUT_FILENO);
	pipefd[1] = STDOUT_FILENO;
}

static void	_pipe_stdout(int pipefd[2])
{
	_dup_and_close(pipefd[0], STDIN_FILENO);
	pipefd[0] = STDIN_FILENO;
}

static void	_pipe(t_ast *ast, t_data *data)
{
	if (ast->type == E_NODE_TYPE_COMMAND)
		exe_cmd(ast, data);
	else
	{
		_pipe(ast->left, data);
		_pipe_stdout(data->pipefd);
		_pipe_stdin(data->pipefd);
		_pipe(ast->right, data);
	}
}

void	exe_pipe(t_ast *ast, t_data *data)
{
	int	fd_in;
	int	fd_out;

	fd_in = dup(STDIN_FILENO);
	fd_out = dup(STDOUT_FILENO);
	_pipe_stdin(data->pipefd);
	_pipe(ast->left, data);
	_dup_and_close(fd_out, 1);
	_pipe_stdout(data->pipefd);
	exe_cmd(ast->right, data);
	_dup_and_close(fd_in, 0);
}
