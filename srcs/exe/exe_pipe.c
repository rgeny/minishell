/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 09:48:32 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/03 23:08:16 by buschiix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "struct.h"
#include "exe.h"

static void	_pipe(t_node *cmd, t_data *data)
{
	if (cmd->type == E_NODE_TYPE_COMMAND)
		exe_cmd(cmd, data);
	else
	{
		_pipe(cmd->left, data);
		if (data->fd_in != 0)
			close(data->fd_in);
		data->fd_in = data->pipefd[0];
		close(data->pipefd[1]);
		pipe(data->pipefd);
		_pipe(cmd->right, data);
	}
}
#include <stdio.h>
void	exe_pipe(t_node *cmd, t_data *data)
{
	int	fd_in;
	int	fd_out;

	fd_in = dup(0);
	fd_out = dup(1);
	pipe(data->pipefd);
	data->fd_in = 0;

	_pipe(cmd->left, data);
	dup2(fd_out, 1);
	close(fd_out);
	if (data->fd_in != 0)
		close(data->fd_in);
	data->fd_in = data->pipefd[0];
	close(data->pipefd[1]);
	data->pipefd[1] = 1;

	_pipe(cmd->right, data);
	dup2(fd_in, 0);
	close(fd_in);
	close(data->pipefd[0]);
}
/*	int	pipefd[2];

	pipe(pipefd);
	if (cmd->left->command->fd_out == 1)
	{
		cmd->left->command->fd_out = pipefd[1];
		cmd->left->command->fd_tmp = pipefd[0];
	}
	if (cmd->right->command->fd_in == 0)
	{
		cmd->right->command->fd_in = pipefd[0];
		cmd->right->command->fd_tmp = pipefd[1];
	}*/


//	close(pipefd[1]);


//	close(pipefd[0]);
