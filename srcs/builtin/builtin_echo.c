/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 18:20:42 by rgeny             #+#    #+#             */
/*   Updated: 2022/01/01 12:57:17 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "str.h"
#include "builtin.h"

static t_echo	static_flag(int argc, char *argv[])
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		if (argv[i][0] == '-')
		{
			j = 1;
			while (argv[i][j] == 'n')
				j++;
			if (argv[i][j])
				return (i);
		}
		else
			return (i);
		i++;
	}
	return (i);
}

int	main(int argc, char *argv[])
{
	int		ret;
	int		i;

	ret = static_flag(argc, argv);
	i = ret;
	while (i < argc)
	{
		write(1, argv[i], str_len(argv[i], 0));
		i++;
		if (i < argc)
			write(1, " ", 1);
	}
	if (ret == 1)
		write(1, "\n", 1);
	return (0);
}
