/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_del.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 20:09:21 by rgeny             #+#    #+#             */
/*   Updated: 2021/12/29 22:59:31 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <stdlib.h>

void	env_del_one(t_env *env)
{
	t_env	*tmp;

	if (!env)
		return ;
	if (env->prev)
		env->prev->next = env->next;
	if (env->next)
		env->next->prev = env->prev;
	free(env->name);
	if (env->value)
		free(env->value);
	free(env);
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
