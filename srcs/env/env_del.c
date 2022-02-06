/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_del.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 20:09:21 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/06 15:48:17 by rgeny            ###   ########.fr       */
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
	if (var->next != NULL)
		var->next->prev = var->prev;
	if (var->prev != NULL)
		var->prev->next = var->next;
	else
		*env = var->next;
	str_free(var->name);
	str_free(var->value);
	free(var);
}

void	env_del_all(t_env *env)
{
	t_env	*next;

	while (env != NULL)
	{
		next = env->next;
		str_free(env->name);
		str_free(env->value);
		free(env);
		env = next;
	}
}
