/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 17:39:59 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/13 12:20:52 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_signal.h"

static void	_sigint(int sig)
{
	(void)sig;
	error_print(NULL, NULL, NULL, SIGINT + SIG_ERROR);
	close(0);
}

void	signal_heredoc(void)
{
	signal(SIGINT, _sigint);
}
