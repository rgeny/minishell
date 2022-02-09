/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 15:40:23 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/08 19:59:11 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void	expand_quote(char *s)
{
	int		i;
	int		len;

	i = 0;
	while (s[i])
	{
		if (uti_is_in_charset(s[i], QUOTES))
		{
			len = str_clen(s + i + 1, s[i]);
			mem_cpy(s, s + i + 1, len);
			i++;
			s += len;
		}
		else
		{
			*s = s[i];
			s++;
		}
	}
	uti_bzero(s, str_len(s));
}