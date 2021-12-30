/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_ndup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 18:10:24 by tokino            #+#    #+#             */
/*   Updated: 2021/12/30 14:22:55 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include "utils.h"
#include "mem.h"

char	*str_ndup(const char *s, int n)
{
	char	*dup;

	if (!s)
		return (0);
	dup = uti_calloc(n + 1, sizeof(char));
	if (dup == NULL)
		return (NULL);
	mem_cpy(dup, s, uti_min(n, str_len(s, 0)));
	if (n > str_len(s, 0))
		mem_set(dup + str_len(s, 0), '\0', n - str_len(s, 0));
	return (dup);
}
