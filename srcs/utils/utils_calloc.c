/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_calloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 18:46:29 by tokino            #+#    #+#             */
/*   Updated: 2022/02/08 20:07:33 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	*uti_calloc(size_t count, size_t size)
{
	void	*dst;

	dst = malloc(count * size);
	if (dst == NULL)
	{
		if (!is_error())
			error_print(MALLOC_ERROR, NULL, NULL, ERROR_MALLOC);
		return (NULL);
	}
	uti_bzero(dst, count * size);
	return (dst);
}
