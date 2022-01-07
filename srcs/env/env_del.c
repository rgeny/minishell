/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_del.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 20:09:21 by rgeny             #+#    #+#             */
/*   Updated: 2022/01/07 23:22:38 by buschiix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "env.h"
#include "str.h"

void	env_del_one(t_env *env)
{
	if (!env)
		return ;
	if (env->prev)
		env->prev->next = env->next;
	if (env->next)
		env->next->prev = env->prev;
	str_free(env->name);
	str_free(env->value);
	if (env)
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
