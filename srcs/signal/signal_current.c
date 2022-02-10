/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_current.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 20:36:37 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/10 14:55:37 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include "str.h"
#include "error.h"

static void	_sigint(int sig)
{
	g_last_return = 128 + sig;
	write(1, "\n\033[31m\033[01m> \033[37m\033[00m", 23);
	rl_prompt = str_dup("abc");
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	signal_current(void)
{
	signal(SIGINT, _sigint);
	signal(SIGQUIT, SIG_IGN);
}
