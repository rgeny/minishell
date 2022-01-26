/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 22:32:54 by rgeny             #+#    #+#             */
/*   Updated: 2022/01/26 20:02:37 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "env.h"
#include "str.h"

#include <stdio.h>

char	*expander_path(char **cmd, t_env *env)
{
	int		i;
	char	**split;
	char	*s;

	if (!access(cmd[0], F_OK | X_OK))
		return (cmd[0]);
	env = env_find(env, "PATH");
	if (!env)
		return (0);
	split = str_split(env->value, ":");
	i = 0;
	while (split && split[i])
	{
		s = str_join(split[i], cmd[0], '/');
		if (!access(s, F_OK | X_OK))
		{
			str_free_list(split);
			return (s);
		}
		str_free(s);
		i++;
	}
	str_free_list(split);
	return (0);
}
