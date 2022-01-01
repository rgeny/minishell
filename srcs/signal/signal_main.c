/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 15:51:31 by rgeny             #+#    #+#             */
/*   Updated: 2022/01/01 17:03:37 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <stdio.h>

#include <unistd.h>
#include <stdlib.h>

static void	handler	(int sig)
{
	if (sig == SIGINT)
		printf("t1\n");
}

int	main(void)
{
	char				*s;

	signal(, handler);	

	s = readline("> ");
	while (strcmp(s, "exit"))
	{
		printf("%s\n", s);
		s = readline("> ");
	}
}
