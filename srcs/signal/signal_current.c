/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_current.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 20:36:37 by rgeny             #+#    #+#             */
/*   Updated: 2022/01/25 11:42:13 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include "struct.h"
#include "str.h"

static int	*g_ret = 0;

void	_sigint(int sig)
{
	*g_ret = 128 + sig;
	write(1, "\n\033[31m\033[01m> \033[37m\033[00m", 23);
	rl_prompt = str_dup("abc");
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
	while (next_history())
		;
}

void	signal_current(t_data *data)
{
	if (data)
		g_ret = &data->ret;
	signal(SIGINT, _sigint);
	signal(SIGQUIT, SIG_IGN);
}
