/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 09:48:32 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/10 14:52:52 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

static void	_dup_and_close_fd(int oldfd, int newfd)
{
	dup2(oldfd, newfd);
	close(oldfd);
}

static void	_redir_pipe_stdin(int pipefd[2])
{
	pipe(pipefd);
	_dup_and_close_fd(pipefd[1], STDOUT_FILENO);
	pipefd[1] = STDOUT_FILENO;
}

static void	_redir_pipe_stdout(int pipefd[2])
{
	_dup_and_close_fd(pipefd[0], STDIN_FILENO);
	pipefd[0] = STDIN_FILENO;
}

static void	_loop_exe_pipe(t_ast *ast, t_data *data)
{
	if (ast->is_subshell)
	{
		ast->is_subshell = false;
		ast->pid = fork();
		if (ast->pid == -1)
			exit(1);
		if (ast->pid == 0)
			exe_subshell(ast, data);
	}
	else if (ast->type == E_NODE_TYPE_COMMAND)
		exe_cmd(ast, data);
	else
	{
		_loop_exe_pipe(ast->left, data);
		_redir_pipe_stdout(data->pipefd);
		_redir_pipe_stdin(data->pipefd);
		_loop_exe_pipe(ast->right, data);
	}
}

void	exe_pipe(t_ast *ast, t_data *data)
{
	int	fd_in;
	int	fd_out;

	fd_in = dup(STDIN_FILENO);
	fd_out = dup(STDOUT_FILENO);
	_redir_pipe_stdin(data->pipefd);
	_loop_exe_pipe(ast->left, data);
	_dup_and_close_fd(fd_out, 1);
	_redir_pipe_stdout(data->pipefd);
	_loop_exe_pipe(ast->right, data);
	_dup_and_close_fd(fd_in, 0);
}
