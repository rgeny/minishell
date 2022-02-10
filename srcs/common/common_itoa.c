/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_itoa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 17:07:01 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/10 17:51:58 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static int	_size(int n)
{
	if (n < 10)
		return (1);
	else
		return (1 + _size(n / 10));
}

char	*uti_itoa(int n)
{
	int		sz;
	char	*s;

	sz = _size(n);
	s = uti_calloc(sz + 1, sizeof(char));
	if (!s)
		return (0);
	s[sz] = 0;
	while (sz)
	{
		sz--;
		s[sz] = n % 10 + '0';
		n /= 10;
	}
	return (s);
}
