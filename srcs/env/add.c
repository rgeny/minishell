/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 19:19:47 by rgeny             #+#    #+#             */
/*   Updated: 2021/12/14 19:38:52 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	env_add_back(t_env **env, t_env *new)
{
	t_env	*tmp;

	if (!(*env))
		*env = new;
	else
	{
		tmp = *env;
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
}
