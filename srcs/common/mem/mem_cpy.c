/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_cpy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 14:45:17 by tokino            #+#    #+#             */
/*   Updated: 2022/02/10 18:28:40 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

void	*mem_cpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*c_dst;
	unsigned char	*c_src;

	i = -1;
	c_dst = (unsigned char *)dst;
	c_src = (unsigned char *)src;
	if (c_dst == NULL && c_src == NULL)
		return (NULL);
	while (++i < n)
		c_dst[i] = c_src[i];
	return (dst);
}
