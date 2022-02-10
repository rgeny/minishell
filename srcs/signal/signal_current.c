/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_current.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 20:36:37 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/10 18:36:27 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_signal.h"

static void	_sigint(int sig)
{
	g_last_return = SIG_ERROR + sig;
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	signal_current(void)
{
	signal(SIGINT, _sigint);
	signal(SIGQUIT, SIG_IGN);
}
