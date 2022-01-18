/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 15:08:49 by rgeny             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/01/18 05:30:15 by buschiix         ###   ########.fr       */
=======
/*   Updated: 2022/01/09 16:52:05 by buschiix         ###   ########.fr       */
>>>>>>> 04f73bbad60a81c69f99fba12a7d24cd76b360c0
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "str.h"
#include "env.h"
#include "struct.h"

<<<<<<< HEAD
static void	_add_back(t_env **env, t_env *new)
=======
#include <stdio.h>

static void	static_add_back(t_env **env, t_env *new)
>>>>>>> 04f73bbad60a81c69f99fba12a7d24cd76b360c0
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

	new = env_find(*env, name);
	if (new)
	{
		env_assign(*env, name, value);
		str_free(name);
		return ;
	}
	new = malloc(sizeof(t_env));
	if (!new)
	{
		printf("t1\n");
		return ;
	}
	new->name = name;
	new->value = value;
	new->next = 0;
	new->prev = 0;
	_add_back(env, new);
}
