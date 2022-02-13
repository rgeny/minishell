/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_fork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buschiix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 00:55:13 by buschiix          #+#    #+#             */
/*   Updated: 2022/02/13 12:41:10 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_signal.h"

static void	_sigint_fork(int sig)
{
	int	fd;

	fd = open("abc", O_WRONLY | O_CREAT);
	write(fd, "abc", 3);
	close(fd);
}

void	signal_fork(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
