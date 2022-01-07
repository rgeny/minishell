/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_iswhat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buschiix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 18:56:00 by buschiix          #+#    #+#             */
/*   Updated: 2022/01/07 18:58:49 by buschiix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	uti_iswhat(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (IS_ALPHA);
	else if (c == '_')
		return (IS_UNDER);
	else if (c >= '0' && c <= '9')
		return (IS_NUM);
	else
		return (IS_OTHER);
}
