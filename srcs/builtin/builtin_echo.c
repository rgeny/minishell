/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 18:20:42 by rgeny             #+#    #+#             */
/*   Updated: 2021/12/31 19:03:20 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "str.h"
#include "builtin.h"

static t_echo	static_flag(int argc, char *flag)
{
	if (argc > 1 && !str_cmp("-n", flag))
		return (FLAG_N);
	return (FLAG_NO);
}

int	main(int argc, char *argv[])
{
	t_echo	echo;
	int		i;

	echo = static_flag(argc, argv[1]);
	if (echo == FLAG_NO)
		i = 1;
	else
		i = 2;
	while (i < argc)
	{
		write(1, argv[i], str_len(argv[i], 0));
		i++;
		if (i < argc)
			write(1, " ", 1);
	}
	if (echo == FLAG_NO)
		write(1, "\n", 1);
	return (0);
}
