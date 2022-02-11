/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 15:40:23 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/11 19:36:13 by rgeny            ###   ########.fr       */
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
		if (is_in_charset(s[i], QUOTES)
			&& str_len(&s[i + 1]) != str_clen(&s[i + 1], s[i]))
		{
			len = str_clen(s + i + 1, s[i]);
			mem_cpy(s, s + i + 1, len);
			i += 2;
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
