/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_switch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 18:18:23 by rgeny             #+#    #+#             */
/*   Updated: 2022/01/18 18:06:41 by buschiix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "env.h"
#include "str.h"

static int	_size(t_env *env, int with_not_init)
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

static void	_assign(t_env *tmp, int with_not_init, char **ret)
{
	int	i;

	i = 0;
	while (tmp)
	{
		if (with_not_init || tmp->value)
		{
			if (tmp->value)
				ret[i] = str_join(tmp->name, tmp->value, '=');
			else
				ret[i] = str_ndup(tmp->name, str_len(tmp->name));
			i++;
		}
		tmp = tmp->next;
	}
	ret[i] = 0;
}

char	**env_switch(t_data *data, int with_not_init)
{
	int		sz;
	char	**ret;

	env_assign(data->env, "PWD", str_ndup(data->pwd, str_len(data->pwd)));
	sz = _size(data->env, with_not_init);
	ret = malloc(sizeof(char *) * (sz + 1));
	if (!ret)
		return (0);
	_assign(data->env, with_not_init, ret);
	return (ret);
}
