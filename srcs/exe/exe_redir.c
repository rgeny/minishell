/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 08:52:26 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/09 14:48:42 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "t_ast.h"
#include "error.h"

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
		return (-1);
	return (0);
}

static int	_open_redir(t_command *cmd, int last_heredoc)
{
	// static mode_t	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	// static int		o_write = O_WRONLY | O_CREAT;
	// int				i;

	// i = 0;
	// while (i < cmd->redir_nb)
	// {
	// 	if (cmd->redirections[i].type == E_REDIR_TYPE_STDIN && i > last_heredoc)
	// 	{
	// 		if (_open(&cmd->fd_in, cmd->redirections[i].path, O_RDONLY, 0) == -1)
	// 			return (error_print(cmd->redirections[i].path, ": No such file or directory\n", 0, -1));
	// 	}
	// 	else if (cmd->redirections[i].type == E_REDIR_TYPE_APPEND && i > last_heredoc)
	// 	{
	// 		if (_open(&cmd->fd_out, cmd->redirections[i].path, o_write | O_APPEND, mode) == -1)
	// 			return (error_print(cmd->redirections[i].path, ": No such file or directory\n", 0, -1));
	// 	}
	// 	else if (cmd->redirections[i].type == E_REDIR_TYPE_STDOUT)
	// 	{
	// 		if (_open(&cmd->fd_out, cmd->redirections[i].path, o_write | O_TRUNC, mode) == -1)
	// 			return (error_print(cmd->redirections[i].path, ": No such file or directory\n", 0, -1));
	// 	}
	// 	i++;
	// }
	return (0);
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

int	exe_redir(t_command *cmd)
{
// 	int	last_heredoc;

// 	if (cmd->redir_nb)
// 	{
// 		last_heredoc = _last_heredoc(cmd->redirections, cmd->redir_nb - 1);
// 		if (_open_redir(cmd, last_heredoc) == -1)
// 			return (-1);
// 		_redir(cmd->fd_in, cmd->fd_out);
// 	}
	return (0);
}
