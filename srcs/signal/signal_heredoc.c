/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 17:39:59 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/07 19:31:21 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <unistd.h>
#include "error.h"

static void	_sigint(int sig)
{
	error_print(NULL, NULL, NULL, SIGINT + SIG_ERROR);
	close(0);
}

void	signal_heredoc(void)
{
	signal(SIGINT, _sigint);
}
