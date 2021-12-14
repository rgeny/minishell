/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 21:31:46 by tokino            #+#    #+#             */
/*   Updated: 2020/11/20 21:31:56 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_nsize(unsigned int n)
{
	int	size;

	if (n < 10)
		size = 1;
	else
		size = get_nsize(n / 10) + 1;
	return (size);
}

char	*ft_itoa(int n)
{
	int				len;
	int				is_neg;
	unsigned int	unbr;
	char			*dst;

	is_neg = (n < 0);
	if (is_neg)
		unbr = (unsigned int)n * -1;
	else
		unbr = n;
	len = is_neg + get_nsize(unbr);
	dst = (char *)ft_calloc(len + 1, sizeof(char));
	if (dst == NULL)
		return (NULL);
	if (is_neg)
		dst[0] = '-';
	len--;
	while (len >= is_neg)
	{
		dst[len] = unbr % 10 + '0';
		unbr /= 10;
		len--;
	}
	return (dst);
}
