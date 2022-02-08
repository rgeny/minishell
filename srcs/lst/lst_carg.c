/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_carg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 14:47:46 by tokino            #+#    #+#             */
/*   Updated: 2022/02/08 11:00:56 by buschiix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lst.h"
#include "error.h"
#include <stdlib.h>
#include "utils.h"

void	lst_carg_add_back(t_carg **lst, t_carg *new)
{
	t_carg	*current;

	if (error_get() != SUCCESS)
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
#include <stdio.h>
void	lst_new_after(t_carg *current, char *new_content)
{
	t_carg	*new;

	if (current == NULL || new_content == NULL)
		return ;
	new = uti_calloc(1, sizeof(t_carg));
	if (new == NULL)
		return ;
	new->content = str_dup(new_content);
	if (new->content == NULL)
	{
		free(new);
		return ;
	}
	new->next = current->next;
	current->next = new;
}
