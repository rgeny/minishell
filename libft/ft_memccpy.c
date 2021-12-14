/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 15:05:30 by tokino            #+#    #+#             */
/*   Updated: 2020/11/14 15:05:32 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*c_dst;
	unsigned char	*c_src;

	i = 0;
	c_dst = (unsigned char *)dst;
	c_src = (unsigned char *)src;
	if (c_dst == NULL && c_src == NULL)
	{
		return (NULL);
	}
	while (i < n)
	{
		c_dst[i] = c_src[i];
		if (c_src[i] == (unsigned char)c)
		{
			return (c_dst + i + 1);
		}
		i++;
	}
	return (NULL);
}
