/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 21:26:03 by tokino            #+#    #+#             */
/*   Updated: 2020/11/14 21:26:05 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
	{
		return (0);
	}
	i = 0;
	while (s1 && s1[i] && s2 && s2[i] && i < n && s1[i] == s2[i])
	{
		i++;
	}
	if (i == n)
	{
		i--;
	}
	return ((int)((unsigned char)s1[i] - (unsigned char)s2[i]));
}
