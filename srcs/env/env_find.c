/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_find.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 21:18:35 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/06 15:52:38 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

t_env	*env_find_var(t_env *env, const char *name)
{
	if (env == NULL)
		return (NULL);
	while (env->prev != NULL)
		env = env->prev;
	while (env && str_cmp(env->name, name) != 0)
		env = env->next;
	return (env);
}

char	*env_find_val(t_env *env, const char *name)
{
	t_env	*var;

	var = env_find_var(env, name);
	if (var != NULL)
		return (var->value);
	return (NULL);
}

char	*env_find_name(t_env *env, const char *name)
{
	t_env	*var;

	var = env_find_var(env, name);
	if (var != NULL)
		return (var->name);
	return (NULL);
}
