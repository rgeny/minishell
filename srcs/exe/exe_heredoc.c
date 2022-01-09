/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buschiix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 13:10:45 by buschiix          #+#    #+#             */
/*   Updated: 2022/01/09 13:29:58 by buschiix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include "str.h"

static void	_son(int pipefd[2], char *delimiter)
{
	char	*s;

	s = readline("> ");
	while (str_cmp(s, delimiter))
	{
		write(pipefd[1], s, str_len(s, 0));
		write(pipefd[1], "\n", 1);
		free(s);
		s = readline("> ");
	}
	free(s);
	close(pipefd[0]);
	close(pipefd[1]);
	exit(0);
}

int	exe_heredoc(char *delimiter)
{
	int		pipefd[2];
	pid_t	pid;

	pipe(pipefd);
	pid = fork();
	if (!pid)
		_son(pipefd, delimiter);
	waitpid(pid, 0, 0);
	close(pipefd[1]);
	return (pipefd[0]);
}
