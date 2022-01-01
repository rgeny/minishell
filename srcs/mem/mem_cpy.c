/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 14:45:17 by tokino            #+#    #+#             */
/*   Updated: 2021/12/15 14:37:41 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

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