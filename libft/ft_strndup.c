/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 18:10:24 by tokino            #+#    #+#             */
/*   Updated: 2021/12/09 21:29:05 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, int n)
{
	char	*dup;

	dup = (char *)ft_calloc(n + 1, sizeof(char));
	if (dup == NULL)
	{
		return (NULL);
	}
	ft_memcpy(dup, s, get_min(n, ft_strlen(s)));
	if (n > ft_strlen(s))
	{
		ft_memset(dup + ft_strlen(s), '\0', n - ft_strlen(s));
	}
	return (dup);
}
