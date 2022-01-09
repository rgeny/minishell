/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_current.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 20:36:37 by rgeny             #+#    #+#             */
/*   Updated: 2022/01/09 01:29:20 by buschiix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <readline/readline.h>
#include <unistd.h>
#include "struct.h"

static int	*g_ret = 0;

void	_sigint(int sig)
{
	*g_ret = 128 + sig;
	write(1, "\n\033[31m\033[01m> \033[37m\033[00m", 23);
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	signal_current(t_data *data)
{
	if (data)
		g_ret = &data->ret;
	signal(SIGINT, _sigint);
	signal(SIGQUIT, SIG_IGN);
}
