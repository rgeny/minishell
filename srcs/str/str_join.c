/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_join.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 18:47:50 by rgeny             #+#    #+#             */
/*   Updated: 2022/01/18 19:02:43 by buschiix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "mem.h"
#include "str.h"

char	*str_join(const char *s1, const char *s2, char c)
{
	int		sz1;
	int		sz2;
	char	*dst;

	if (!s1 || !s2)
		return (0);
	sz1 = str_len((char *)s1);
	sz2 = str_len((char *)s2);
	dst = malloc(sizeof(char) * (sz1 + sz2 + 1 + !(!c)));
	if (!dst)
		return (0);
	dst[sz1 + sz2 + !!c] = 0;
	mem_cpy(dst, s1, sz1);
	dst[sz1] = c;
	mem_cpy(dst + sz1 + !(!c), s2, sz2);
	return (dst);
}
