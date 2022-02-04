/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_find.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 21:18:35 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/04 23:39:36 by buschiix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "env.h"
#include "str.h"

t_env	*env_find_var(t_env *env, char *name)
{
	while (env && env->prev)
		env = env->prev;
	while (env && str_cmp(env->name, name))
		env = env->next;
	return (env);
}

char	*env_find_value(t_env *env, char *name)
{
	t_env	*var;

	var = env_find_var(env, name);
	if (var)
		return (var->value);
	return (NULL);
}

char	*env_find_name(t_env *env, char *name)
{
	t_env	*var;

	var = env_find_var(env, name);
	if (var)
		return (var->name);
	return (NULL);
}
