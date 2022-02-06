/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ato.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 17:27:14 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/06 16:06:46 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	uti_atoi(char *s)
{
	long	n;
	int		i;

	if (s == NULL)
		return (0);
	n = 0;
	i = 0;
	while (s[i])
	{
		n = n * 10 + s[i] - '0';
		if (n > 2147483647)
			return (0);
		i++;
	}
	return (n);
}

long	uti_atol(char *s)
{
	unsigned long	n;
	int				i;
	int				sign;

	sign = 1;
	i = 0;
	if (s[0] == '-')
	{
		sign = -1;
		i = 1;
	}
	n = 0;
	while (s[i])
	{
		n = n * 10 + s[i] - '0';
		if ((sign == 1 && n > 9223372036854775807)
			|| (sign == -1 && n - 1 > 9223372036854775807))
		{
			s[0] = ')';
			return (0);
		}
		i++;
	}
	return (n * sign);
}
