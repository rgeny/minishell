/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 08:52:26 by rgeny             #+#    #+#             */
/*   Updated: 2022/01/28 10:39:29 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "struct.h"

#include <stdio.h>

static int	_last_heredoc(t_redir *redir, int size)
{
	while (size && redir[size].type != E_REDIR_TYPE_HEREDOC)
		size--;
	return (size);
}

static void	_open_redir(t_command *cmd, int last_heredoc)
{
	int	i;

	i = 0;
	while (i < cmd->redir_nb)
	{
		if (cmd->redirections[i].type == E_REDIR_TYPE_STDIN && i > last_heredoc)
		{
			if (cmd->fd_in != 0)
				close(cmd->fd_in);
			cmd->fd_in = open(cmd->redirections[i].path, O_RDONLY);
		}
		else if (cmd->redirections[i].type == E_REDIR_TYPE_STDOUT)
		{
			if (cmd->fd_in != 1)
				close(cmd->fd_in);
			cmd->fd_in = open(cmd->redirections[i].path, O_WRONLY);
		}
		i++;
	}
}

static void	_redir(int fd_in, int fd_out)
{
	if (fd_in != 0)
	{
		dup2(fd_in, 0);
		close(fd_in);
	}
	if (fd_out != 1)
	{
		dup2(fd_out, 1);
		close(fd_out);
	}
}

void	exe_redir(t_command *cmd)
{
	int	last_heredoc;

	if (cmd->redir_nb)
	{
		last_heredoc = _last_heredoc(cmd->redirections, cmd->redir_nb - 1);
		_open_redir(cmd, last_heredoc);
		_redir(cmd->fd_in, cmd->fd_out);
	}
}
