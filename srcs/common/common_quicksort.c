/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_quicksort.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buschiix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 18:39:37 by buschiix          #+#    #+#             */
/*   Updated: 2022/02/10 18:25:24 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static int	_find_pivot(int start, int end, char **s)
{
	while (start < end && str_cmp(s[start], s[end]) < 0)
		start++;
	return (start);
}

static int	_sort(int pivot, int end, char **s)
{
	int		i;
	char	*tmp;

	i = pivot;
	while (i < end)
	{
		if (str_cmp(s[i], s[end]) < 0)
		{
			tmp = s[i];
			s[i] = s[pivot];
			s[pivot] = tmp;
			pivot++;
		}
		i++;
	}
	tmp = s[pivot];
	s[pivot] = s[end];
	s[end] = tmp;
	return (pivot);
}

void	uti_quicksort(int start, int end, char **s)
{
	int	pivot;

	if (end <= start)
		return ;
	pivot = _find_pivot(start, end, s);
	pivot = _sort(pivot, end, s);
	uti_quicksort(start, pivot - 1, s);
	uti_quicksort(pivot + 1, end, s);
}
