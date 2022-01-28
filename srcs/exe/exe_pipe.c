/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 09:48:32 by rgeny             #+#    #+#             */
/*   Updated: 2022/01/28 10:07:26 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "struct.h"
#include "exe.h"

void	exe_pipe(t_node *cmd, t_data *data)
{
	int	pipefd[2];
	int	fd_stdout;
	int	fd_stdin;

	pipe(pipefd);
	fd_stdout = dup(1);
	dup2(pipefd[1], 1);
	fd_stdin = dup(0);
	dup2(pipefd[0], 0);

	exe_main(cmd->left, data);

	dup2(fd_stdout, 1);
	close(fd_stdout);
	close(pipefd[1]);

	exe_main(cmd->right, data);

	dup2(fd_stdin, 0);
	close(fd_stdin);
	close(pipefd[0]);	
}
