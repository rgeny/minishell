/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ndup.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 18:10:24 by tokino            #+#    #+#             */
/*   Updated: 2021/12/14 18:32:50 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*str_ndup(const char *s, int n)
{
	char	*dup;

	dup = malloc(sizeof(char) * (n + 1));
	if (dup == NULL)
		return (NULL);
	mem_cpy(dup, s, get_min(n, str_len(s)));
	if (n > str_len(s))
		mem_set(dup + str_len(s), '\0', n - str_len(s));
	return (dup);
}
