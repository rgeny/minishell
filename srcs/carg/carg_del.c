/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carg_del.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 16:01:21 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/10 16:01:43 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "carg.h"

void	carg_del_one(t_carg **args, t_command *cmd)
{
	t_carg	*next;
	t_carg	*prev;

	if (cmd->cargs == *args)
		cmd->cargs = (*args)->next;
	else
	{
		prev = cmd->cargs;
		while (prev->next != *args)
			prev = prev->next;
		prev->next = (*args)->next;
	}
	str_free(&(*args)->content);
	next = (*args)->next;
	free(*args);
	*args = next;
}
