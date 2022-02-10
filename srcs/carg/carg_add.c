/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carg_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 16:02:24 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/10 16:02:45 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "carg.h"

void	carg_add_back(t_carg **lst, t_carg *new)
{
	t_carg	*current;

	if (is_error())
		return ;
	current = *lst;
	while (current && current->next)
		current = current->next;
	if (current)
		current->next = new;
	else
		*lst = new;
}
