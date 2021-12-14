/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_del.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 21:01:51 by rgeny             #+#    #+#             */
/*   Updated: 2021/12/14 21:23:23 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	env_del(t_env **env, char *s)
{
	t_env	*node;

	node = env_find(*env, s);
	if (node)
	{
		if (node->prev)
			node->prev->next = node->next;
		if (node->next)
			node->next->prev = node->prev;
		if (node == *env)
		{
			if (node->prev)
				*env = node->prev;
			else
				*env = node->next;
		}
		free(node->name);
		free(node->value);
		free(node);
	}
}
