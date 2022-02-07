/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_carg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 14:47:46 by tokino            #+#    #+#             */
/*   Updated: 2022/02/07 15:16:30 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lst.h"
#include "error.h"

void	lst_carg_add_back(t_carg **lst, t_carg *new)
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

void	lst_carg_add_after(t_carg *after, t_carg *new)
{
	t_carg	*tmp;

	if (!after || !new)
		return ;
	tmp = after->next;
	after->next = new;
	new->next = tmp;
}
