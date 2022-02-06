/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_switch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 18:18:23 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/06 17:14:28 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static int	_env_size(t_env *env, bool with_not_init)
{
	int	i;

	i = 0;
	while (env != NULL)
	{
		if (with_not_init == true || env->value != NULL)
			i++;
		env = env->next;
	}
	return (i);
}

static void	_switch(t_env *env, bool with_not_init, char **envp)
{
	int	i;

	i = 0;
	while (env != NULL)
	{
		if (with_not_init == true || env->value != NULL)
		{
			envp[i] = str_join(env->name, env->value, '=');
			i++;
		}
		env = env->next;
	}
}

char	**env_switch(t_data *data, bool with_not_init)
{
	int		sz;
	char	**envp;

	env_assign(data->env, ENV_PWD, str_dup(data->pwd));
	sz = _env_size(data->env, with_not_init);
	envp = uti_calloc(sz + 1, sizeof(char *));
	if (envp == NULL)
		return (NULL);
	_switch(data->env, with_not_init, envp);
	return (envp);
}
