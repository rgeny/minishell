/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_len.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 14:13:56 by tokino            #+#    #+#             */
/*   Updated: 2022/02/10 18:12:45 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

int	str_llen(char **s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	str_clen(const char *s, char c)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

int	str_len(const char *s)
{
	return (str_clen(s, 0));
}

int	str_len_alnum(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (is_alnum(s[i]))
		i++;
	return (i);
}
