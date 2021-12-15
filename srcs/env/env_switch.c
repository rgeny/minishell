/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_switch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 18:18:23 by rgeny             #+#    #+#             */
/*   Updated: 2021/12/15 18:24:54 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "str.h"
#include <stdlib.h>

static int	static_size(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char	**env_switch(t_env *env)
{
	int		sz;
	char	**ret;
	int		i;

	sz = static_size(env);
	ret = malloc(sizeof(char *) * (sz + 1));
	if (!ret)
		return (0);
	i = 0;
	while (env)
	{
		ret[i] = str_join(env->name, env->value, '=');
		env = env->next;
		i++;
	}
	ret[i] = 0;
	return (ret);
}
