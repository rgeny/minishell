/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_del.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 20:09:21 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/06 15:32:11 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "env.h"
#include "str.h"

void	env_del_one(t_env **env, char *name)
{
	t_env	*var;

	var = env_find_var(*env, name);
	if (var == NULL)
		return ;
	if (var->prev)
		var->prev->next = var->next;
	else
		*env = var->next;
	if (var->next)
		var->next->prev = var->prev;
	str_free(var->name);
	str_free(var->value);
	free(var);
}

void	env_del_all(t_env *env)
{
	t_env	*next;

	while (env)
	{
		next = env->next;
		str_free(env->name);
		str_free(env->value);
		free(env);
		env = next;
	}
}
