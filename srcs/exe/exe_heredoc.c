/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buschiix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 13:10:45 by buschiix          #+#    #+#             */
/*   Updated: 2022/01/15 02:54:53 by buschiix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include "str.h"
#include <signal.h>
#include "minishell_signal.h"

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

int	exe_heredoc(char *delimiter, t_data *data)
{
	int		pipefd[2];
	pid_t	pid;
	int		status;

	pipe(pipefd);
	pid = fork();
	if (!pid)
	{
		signal(SIGINT, SIG_DFL);
		_son(pipefd, delimiter);
	}
	signal_ignore();
	waitpid(pid, &status, 0);
	signal_current(0);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
		{
			data->ret = WTERMSIG(status) + 128;
			close(pipefd[0]);
			pipefd[0] = -1;
		}
		write(1, "\n", 1);
	}
	close(pipefd[1]);
	return (pipefd[0]);
}
