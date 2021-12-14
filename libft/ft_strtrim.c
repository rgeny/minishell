/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 15:10:05 by tokino            #+#    #+#             */
/*   Updated: 2020/11/19 15:10:20 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_set(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set && set[i])
	{
		if (c == set[i])
		{
			return (1);
		}
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	len;
	char	*dst;

	if (s1 == NULL)
		return (NULL);
	start = 0;
	while (is_in_set(s1[start], set))
		start++;
	len = ft_strlen(s1 + start);
	while (len > 0 && is_in_set(s1[start + len - 1], set))
		len--;
	dst = malloc(len + 1);
	if (dst == NULL)
		return (NULL);
	ft_memcpy(dst, s1 + start, len);
	dst[len] = '\0';
	return (dst);
}
