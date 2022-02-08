/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 08:52:26 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/10 02:09:13 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "t_ast.h"
#include "error.h"
#include "d_redir.h"

static int	_last_heredoc(t_redir *redir, int n_redir)
{
	while (n_redir >= 0 && redir[n_redir].type != E_REDIR_TYPE_HEREDOC)
		n_redir--;
	return (n_redir);
}

static int	_open(int *fd, char *path, int flag, mode_t mode)
{
	if (*fd > 1)
		close(*fd);
	if (!mode)
		access(path, F_OK);
	*fd = open(path, flag, mode);
	if (*fd == -1)
		return (error_print(path, NO_FILE, NULL, ERROR_EXEC));
	return (0);
}

static int	_error_close_fd(t_command *cmd)
{
	if (cmd->fd_in != STDIN_FILENO)
		close(cmd->fd_in);
	if (cmd->fd_out != STDOUT_FILENO)
		close(cmd->fd_out);
	return (error_get());
}
#include <stdio.h>
static int	_open_redir(t_command *cmd, int last_heredoc)
{
	int				i;

	i = 0;
	while (i < cmd->redir_nb)
	{
		if (cmd->redirections[i].type == E_REDIR_TYPE_STDIN && i > last_heredoc)
		{
			if (_open(&cmd->fd_in, cmd->redirections[i].path, O_RDONLY, 0) == -1)
				return (_error_close_fd(cmd));
		}
		else if (cmd->redirections[i].type == E_REDIR_TYPE_APPEND && i > last_heredoc)
		{
			if (_open(&cmd->fd_out, cmd->redirections[i].path, o_write | O_APPEND, CREATE_MODE) == -1)
				return (_error_close_fd(cmd));
		}
		else if (cmd->redirections[i].type == E_REDIR_TYPE_STDOUT)
		{
			if (_open(&cmd->fd_out, cmd->redirections[i].path, o_write | O_TRUNC, CREATE_MODE) == -1)
				return (_error_close_fd(cmd));
		}
		i++;
	}
	return (SUCCESS);
}

static void	_redir(int fd_in, int fd_out)
{
	if (fd_in != 0 && fd_in != -1)
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
		if (_open_redir(cmd, last_heredoc) != SUCCESS)
			return ;
		_redir(cmd->fd_in, cmd->fd_out);
	}
	return (0);
}
