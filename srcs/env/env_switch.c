/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_switch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 18:18:23 by rgeny             #+#    #+#             */
/*   Updated: 2022/01/01 18:08:08 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "env.h"
#include "str.h"
#include "global.h"

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

static void	static_assign(t_env *tmp, int with_not_init, char **ret)
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
				ret[i] = str_ndup(tmp->name, str_len(tmp->name, 0));
			i++;
		}
		tmp = tmp->next;
	}
	ret[i] = 0;
}

char	**env_switch(t_env **env, int with_not_init)
{
	int		sz;
	char	**ret;
	int		i;
	t_env	*tmp;

	tmp = *env;
	env_new(env, str_ndup("PWD", str_len("PWD", 0)),
		str_ndup(glo_pwd(0, 0), str_len(glo_pwd(0, 0), 0)));
	sz = static_size(tmp, with_not_init);
	ret = malloc(sizeof(char *) * (sz + 1));
	if (!ret)
		return (0);
	static_assign(*env, with_not_init, ret);
	return (ret);
}
