/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_ignore.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buschiix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 00:56:29 by buschiix          #+#    #+#             */
/*   Updated: 2022/02/11 16:33:27 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_signal.h"

void	_sigint_nl(int sig)
{
	write(1, "\n", 1);
}

void	signal_ignore(void)
{
	signal(SIGINT, _sigint_nl);
	signal(SIGQUIT, SIG_IGN);
}
