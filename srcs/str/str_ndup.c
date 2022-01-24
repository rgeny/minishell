/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_ndup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 18:10:24 by tokino            #+#    #+#             */
/*   Updated: 2022/01/18 19:02:19 by buschiix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include "utils.h"
#include "mem.h"

char	*str_ndup(const char *s, int n)
{
	char	*dup;
	int		len;

	if (!s)
		return (0);
	dup = uti_calloc(n + 1, sizeof(char));
	if (dup == NULL)
		return (NULL);
	len = str_len(s);
	mem_cpy(dup, s, uti_min(n, len));
	if (n > len)
		mem_set(dup + len, '\0', n - len);
	return (dup);
}
