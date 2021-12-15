/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_del.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 20:09:21 by rgeny             #+#    #+#             */
/*   Updated: 2021/12/15 12:40:06 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <stdlib.h>

void	env_del_one(t_env *env)
{
	t_env	*tmp;

/*	tmp = *env;
	if (tmp)
	{
		if (tmp->prev)
			tmp->prev->next = tmp->next;
		if (tmp->next)
			tmp->next->prev = tmp->prev;
		if (tmp->prev)
			env = &tmp->prev;
		else
			env = &tmp->next;*/
		free(env->name);
		free(env->value);
		free(env);
//	}
}

void	env_del_all(t_env *env)
{
	t_env	*next;

	while (env)
	{
		next = env->next;
		env_del_one(env);
		env = next;
	}
}
