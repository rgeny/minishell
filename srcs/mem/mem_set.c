/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 14:22:28 by tokino            #+#    #+#             */
/*   Updated: 2021/12/15 14:38:10 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*mem_set(void *b, int c, size_t len)
{
	unsigned char	*str_b;

	str_b = (unsigned char *)b;
	while (len > 0)
	{
		*str_b = (unsigned char)c;
		str_b++;
		len--;
	}
	*str_b = 0;
	return (b);
}
