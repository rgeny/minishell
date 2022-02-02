/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 09:48:32 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/02 14:04:53 by buschiix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "struct.h"
#include "exe.h"

/*void	exe_pipe(t_node *cmd, t_data *data)
{
	int	pipefd[2];
	int	fd_stdout;
	int	fd_stdin;

	pipe(pipefd);
	fd_stdin = dup(0);
	fd_stdout = dup(1);
	dup2(pipefd[1], 1);

	exe_main(cmd->left, data);

	dup2(fd_stdout, 1);
	close(fd_stdout);
	close(pipefd[1]);

	exe_main(cmd->right, data);

	dup2(fd_stdin, 0);
	close(fd_stdin);
	close(pipefd[0]);

}*/

static void	_pipe(t_node *cmd, t_data *data, int pipefd[2])
{
	if (cmd->type == E_NODE_TYPE_COMMAND)
		exe_cmd(cmd, data);
	else
	{
		_pipe(cmd->left, data, pipefd);
		
		dup2(pipefd[0], 0);
		close(pipefd[0]);
		close(pipefd[1]);
		pipe(pipefd);
		dup2(pipefd[1], 1);

		_pipe(cmd->right, data, pipefd);
	}
}

void	exe_pipe(t_node *cmd, t_data *data)
{
	int	pipefd[2];
	int	fd_stdout;
	int	fd_stdin;

	if (cmd->type == E_NODE_TYPE_COMMAND)
		exe_cmd(cmd, data);
	else
	{
		pipe(pipefd);
		fd_stdout = dup(1);
		dup2(pipefd[1], 1);
		fd_stdin = dup(0);
		
		_pipe(cmd->left, data, pipefd);

		dup2(fd_stdout, 1);
		close(fd_stdout);
		close(pipefd[1]);
		dup2(pipefd[0], 0);

		_pipe(cmd->right, data, pipefd);

		dup2(fd_stdin, 0);
		close(fd_stdin);
		close(pipefd[0]);
		close(pipefd[1]);
	}
}
