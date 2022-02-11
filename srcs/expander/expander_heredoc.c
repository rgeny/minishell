/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buschiix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 13:10:45 by buschiix          #+#    #+#             */
/*   Updated: 2022/02/11 16:59:40 by rgeny            ###   ########.fr       */
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
		pipefd[1] = STDOUT_FILENO;
		write(STDOUT_FILENO, "\n", 1);
		g_last_return = error_get();
	}
}

static void	_generate_heredoc(int pipefd[2], char *delimiter, t_env *env)
{
	char	*s;
	char	*prompt;

	signal_heredoc();
	prompt = str_join(delimiter, "> ", '\0');
	s = readline(prompt);
	while (s != NULL && str_cmp(s, delimiter) != 0)
	{
		expand_var(&s, env, false);
		str_print_fd_nl(s, pipefd[1]);
		str_free(&s);
		s = readline(prompt);
	}
	signal_current();
	if (s == NULL)
		_handle_errors(pipefd, delimiter);
}

int	expand_heredoc(char *delimiter, t_env *env)
{
	int		pipefd[2];
	int		fd_stdin;

	expand_quote(delimiter);
	fd_stdin = dup(STDIN_FILENO);
	pipe(pipefd);
	_generate_heredoc(pipefd, delimiter, env);
	dup2(fd_stdin, STDIN_FILENO);
	close(fd_stdin);
	close(pipefd[1]);
	return (pipefd[0]);
}
