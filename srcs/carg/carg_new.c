/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carg_new.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 16:03:11 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/10 16:03:49 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "carg.h"

void	carg_new_after(t_carg *current, char *new_content)
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
