/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 19:44:50 by tokino            #+#    #+#             */
/*   Updated: 2020/11/14 19:44:52 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t			i;
	unsigned char	*s2;

	i = 0;
	s2 = (unsigned char *)s;
	while (s2[i])
	{
		if (s2[i] == (unsigned char)c)
		{
			return ((char *)(s2 + i));
		}
		i++;
	}
	if (s2[i] == (unsigned char)c)
	{
		return ((char *)(s2 + i));
	}
	else
	{
		return (NULL);
	}
}
