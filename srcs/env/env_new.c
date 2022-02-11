/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 15:08:49 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/11 14:55:23 by rgeny            ###   ########.fr       */
/*   Updated: 2022/01/09 16:52:05 by buschiix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static void	_add_back(t_env **env, t_env *new)
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

void	env_new(t_env **env, char *name, char *value)
{
	t_env	*new;

	if (name == NULL)
		return (str_free(&value));
	new = env_find_var(*env, name);
	if (new)
	{
		env_assign(*env, name, value);
		str_free(&name);
		return ;
	}
	new = uti_calloc(1, sizeof(t_env));
	if (!new)
		return ;
	new->name = name;
	new->value = value;
	new->next = 0;
	new->prev = 0;
	_add_back(env, new);
}
