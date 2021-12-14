/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 15:45:17 by tokino            #+#    #+#             */
/*   Updated: 2020/11/14 15:45:19 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*c_s;

	i = 0;
	c_s = (unsigned char *)s;
	while (i < n)
	{
		if (c_s[i] == (unsigned char)c)
		{
			return ((void *)(c_s + i));
		}
		i++;
	}
	return (NULL);
}
