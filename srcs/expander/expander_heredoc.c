/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buschiix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 13:10:45 by buschiix          #+#    #+#             */
/*   Updated: 2022/02/07 19:31:25 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static void	_handle_errors(int pipefd[2], char *delimiter)
{
	if (error_get() == 0)
		error_print(HEREDOC, SIG_EOF, delimiter, 0);
	else
	{
		close(pipefd[1]);
		pipefd[1] = -1;
		write(1, "\n", 1);
	}
}

static void	_generate_heredoc(int pipefd[2], char *delimiter)
{
	char	*s;
	char	*prompt;

	signal_heredoc();
	prompt = str_join(delimiter, "> ", '\0');
	s = readline(prompt);
	while (s != NULL && str_cmp(s, delimiter) != 0)
	{
		str_print_fd_nl(s, pipefd[1]);
		str_free(s);
		s = readline(prompt);
	}
	signal_current();
	if (s == NULL)
		_handle_errors(pipefd, delimiter);
}

int	expander_heredoc(char *delimiter)
{
	int		pipefd[2];
	int		fd_stdin;

	fd_stdin = dup(0);
	pipe(pipefd);
	_generate_heredoc(pipefd, delimiter);
	dup2(fd_stdin, 0);
	close(fd_stdin);
	close(pipefd[1]);
	return (pipefd[0]);
}
