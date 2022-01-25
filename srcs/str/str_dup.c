/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_dup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 18:10:24 by tokino            #+#    #+#             */
/*   Updated: 2022/01/25 11:27:34 by tokino           ###   ########.fr       */
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
		return (NULL);
	dup = uti_calloc(n + 1, sizeof(char));
	if (dup == NULL)
		return (NULL);
	len = str_len(s);
	mem_cpy(dup, s, uti_min(n, len));
	if (n > len)
		mem_set(dup + len, '\0', n - len);
	return (dup);
}

char	*str_dup(const char *s)
{
	char	*dup;
	int		len;

	if (!s)
		return (NULL);
	len = str_len(s);
	dup = (char *)uti_calloc(len + 1, sizeof(char));
	if (dup == NULL)
		return (NULL);
	mem_cpy(dup, s, len);
	return (dup);
}
