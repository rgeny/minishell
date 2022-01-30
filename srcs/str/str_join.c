/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_join.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 18:47:50 by rgeny             #+#    #+#             */
/*   Updated: 2022/01/30 11:51:33 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "mem.h"
#include "str.h"
#include "utils.h"

char	*str_join(const char *s1, const char *s2, char c)
{
	int		sz1;
	int		sz2;
	char	*dst;

	if (!s1)
		return (str_dup(s2));
	if (!s2)
		return (str_dup(s1));
	sz1 = str_len((char *)s1);
	sz2 = str_len((char *)s2);
	dst = uti_calloc(sz1 + sz2 + 2, sizeof(char *));
	if (!dst)
		return (NULL);
	mem_cpy(dst, s1, sz1);
	dst[sz1] = c;
	mem_cpy(dst + sz1 + !!c, s2, sz2);
	return (dst);
}
