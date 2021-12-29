/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_switch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 18:18:23 by rgeny             #+#    #+#             */
/*   Updated: 2021/12/29 22:27:15 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "str.h"
#include <stdlib.h>

static int	static_size(t_env *env, int with_not_init)
{
	int	i;

	i = 0;
	while (env)
	{
		if (with_not_init || env->value)
			i++;
		env = env->next;
	}
	return (i);
}

char	**env_switch(t_env *env, int with_not_init)
{
	int		sz;
	char	**ret;
	int		i;

	sz = static_size(env, with_not_init);
	ret = malloc(sizeof(char *) * (sz + 1));
	if (!ret)
		return (0);
	i = 0;
	while (env)
	{
		if (with_not_init || env->value)
		{
			if (env->value)
				ret[i] = str_join(env->name, env->value, '=');
			else
				ret[i] = str_ndup(env->name, str_len(env->name, 0));
			i++;
		}
		env = env->next;
	}
	ret[i] = 0;
	return (ret);
}
