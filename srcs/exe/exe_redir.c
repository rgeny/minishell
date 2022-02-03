/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 08:52:26 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/03 13:39:53 by buschiix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "t_ast.h"
#include "print.h"

static int	_last_heredoc(t_redir *redir, int size)
{
	while (size >= 0 && redir[size].type != E_REDIR_TYPE_HEREDOC)
		size--;
	return (size);
}

static void	_open(int *fd, char *path, int flag, mode_t mode)
{
	if (*fd > 1)
		close(*fd);
	if (!mode)
		access(path, F_OK);
	*fd = open(path, flag, mode);
}

static void	_open_redir(t_command *cmd, int last_heredoc)
{
	static mode_t	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	static int		o_write = O_WRONLY | O_CREAT;
	int				i;

	i = 0;
	while (i < cmd->redir_nb)
	{
		if (cmd->redirections[i].type == E_REDIR_TYPE_STDIN && i > last_heredoc)
			_open(&cmd->fd_in, cmd->redirections[i].path, O_RDONLY, 0);
		else if (cmd->redirections[i].type == E_REDIR_TYPE_APPEND && i > last_heredoc)
			_open(&cmd->fd_out, cmd->redirections[i].path, o_write | O_APPEND, mode);
		else if (cmd->redirections[i].type == E_REDIR_TYPE_STDOUT)
			_open(&cmd->fd_out, cmd->redirections[i].path, o_write | O_TRUNC, mode);
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
