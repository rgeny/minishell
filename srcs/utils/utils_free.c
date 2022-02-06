/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 18:22:01 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/06 18:27:49 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	uti_free(void **p)
{
	if (*p != NULL)
	{
		free(*p);
		*p = NULL;
	}
}
