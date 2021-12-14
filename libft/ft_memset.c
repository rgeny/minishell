/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 14:22:28 by tokino            #+#    #+#             */
/*   Updated: 2020/11/14 14:22:31 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*str_b;

	str_b = (unsigned char *)b;
	while (len > 0)
	{
		*str_b = (unsigned char)c;
		str_b++;
		len--;
	}
	return (b);
}
