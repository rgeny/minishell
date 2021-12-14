/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str2joins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 22:47:10 by vfurmane          #+#    #+#             */
/*   Updated: 2021/12/09 21:27:07 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

char	*ft_str2joins(char const *s1, char const *s2, char const *s3)
{
	char	*dst;
	size_t	s1_len;
	size_t	s2_len;
	size_t	s3_len;

	if (s1 == NULL || s2 == NULL)
	{
		return (NULL);
	}
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	s3_len = ft_strlen(s3);
	dst = (char *)ft_calloc(s1_len + s2_len + s3_len + 1, sizeof(char));
	if (dst == NULL)
	{
		return (NULL);
	}
	ft_memcpy(dst, s1, s1_len + 1);
	ft_memcpy(dst + s1_len, s2, s2_len + 1);
	ft_memcpy(dst + s1_len + s2_len, s3, s3_len + 1);
	return (dst);
}
