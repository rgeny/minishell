/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_split_first.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 18:17:27 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/11 14:55:54 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

char	**str_split_first(char *src, char c)
{
	char	**ret;
	int		len;

	if (!src || !c)
		return (0);
	ret = uti_calloc(3, sizeof(char *));
	len = str_clen(src, c);
	ret[0] = str_ndup(src, len);
	ret[1] = 0;
	if (src[len])
		ret[1] = str_dup(&src[len + 1]);
	ret[2] = 0;
	return (ret);
}
