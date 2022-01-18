/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buschiix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 13:10:45 by buschiix          #+#    #+#             */
/*   Updated: 2022/01/18 11:25:10 by buschiix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <signal.h>
#include "str.h"
#include "error.h"
#include "minishell_signal.h"
#include "print.h"

static void	_son(int pipefd[2], char *delimiter)
{
	char	*s;

	signal(SIGINT, SIG_DFL);
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

static void	_ret_son(int *fd_in, int status, char *delimiter, t_data *data)
{
	if (WIFSIGNALED(status))
	{
		status = WTERMSIG(status);
		if (status == SIGINT)
		{
			data->ret = status + SIGNAL_ERROR;
			close(*fd_in);
			*fd_in = -1;
		}
		else if (status == SIGNAL_EOF)
			print_error("heredoc: ",
				"delimited by the signal EOF instead of word: ",
				delimiter, data);
		write(1, "\n", 1);
	}
}

int	exe_heredoc(char *delimiter, t_data *data)
{
	int		pipefd[2];
	pid_t	pid;
	int		status;

	pipe(pipefd);
	pid = fork();
	if (!pid)
		_son(pipefd, delimiter);
	signal_ignore();
	waitpid(pid, &status, 0);
	signal_current(0);
	_ret_son(&pipefd[0], status, delimiter, data);
	close(pipefd[1]);
	return (pipefd[0]);
}
