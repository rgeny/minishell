/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 13:04:07 by tokino            #+#    #+#             */
/*   Updated: 2020/11/17 14:19:10 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_whitespace(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

static int	ignore_whitespaces(const char *str)
{
	int	i;

	i = 0;
	while (is_whitespace(str[i]))
	{
		i++;
	}
	return (i);
}

long int	ft_atoi(const char *str)
{
	int					i;
	int					sign;
	unsigned long int	nb;

	i = ignore_whitespaces(str);
	nb = 0;
	sign = 1;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
	{
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		nb = nb * 10 + str[i] - '0';
		i++;
	}
	return (sign * nb);
}
