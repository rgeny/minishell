/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_split_first.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 18:17:27 by rgeny             #+#    #+#             */
/*   Updated: 2022/01/25 11:42:49 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "str.h"

char	**str_split_first(char *src, char c)
{
	char	**ret;
	int		len;

	if (!src || !c)
		return (0);
	ret = malloc(sizeof(char *) * 3);
	len = str_clen(src, c);
	ret[0] = str_ndup(src, len);
	ret[1] = 0;
	if (src[len])
		ret[1] = str_dup(&src[len + 1]);
	ret[2] = 0;
	return (ret);
}
