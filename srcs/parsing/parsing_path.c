/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 22:32:54 by rgeny             #+#    #+#             */
/*   Updated: 2022/01/18 10:34:14 by buschiix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "env.h"
#include "str.h"

char	*parsing_path(char **cmd, t_env *env)
{
	int		i;
	char	**split;
	char	*s;

	if (!access(cmd[0], F_OK | X_OK))
		return (0);
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
