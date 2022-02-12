/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_fork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buschiix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 00:55:13 by buschiix          #+#    #+#             */
/*   Updated: 2022/02/12 10:49:04 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_signal.h"

void	_sig(int sig)
{
	write(1, "\n", 1);
}

void	signal_fork(void)
{
	signal(SIGINT, _sig);
	signal(SIGQUIT, _sig);
}
