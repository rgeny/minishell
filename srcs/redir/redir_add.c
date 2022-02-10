/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_add.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 16:17:16 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/10 16:18:10 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

void	redir_add_back(t_redir **lst, t_redir *new)
{
	t_redir	*current;

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
