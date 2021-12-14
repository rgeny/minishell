/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 15:30:54 by tokino            #+#    #+#             */
/*   Updated: 2020/11/14 15:30:56 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*c_dst;
	unsigned char	*c_src;

	i = 0;
	c_dst = (unsigned char *)dst;
	c_src = (unsigned char *)src;
	if (c_src == NULL && c_dst == NULL)
	{
		return (NULL);
	}
	while (i < len)
	{
		if (c_dst < c_src)
		{
			c_dst[i] = c_src[i];
		}
		else
		{
			c_dst[len - 1 - i] = c_src[len - 1 - i];
		}
		i++;
	}
	return (dst);
}
