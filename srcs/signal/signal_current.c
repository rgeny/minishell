/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_current.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 20:36:37 by rgeny             #+#    #+#             */
/*   Updated: 2022/01/08 22:45:11 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <readline/readline.h>
#include <unistd.h>
#include <stdio.h>
#include "struct.h"
#include "exe.h"

static int	*ret = 0;

void	_sigint(int sig)
{
	*ret = 128 + sig;
	write(1, "\n\033[31m\033[01m> \033[37m\033[00m", 23);
	rl_replace_line("",1);
	rl_on_new_line();
	rl_redisplay();
}

void	signal_current(t_data *data)
{
	ret = &data->ret;
	signal(SIGINT, _sigint);
	signal(SIGQUIT, SIG_IGN);
}

/*
ctrl + c = SIGINT
ctrl + d = EOF
ctrl + \ = SIGQUIT (ne fonctionne par en mode interactif)
*/
