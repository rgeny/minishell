/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 22:32:54 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/04 23:44:36 by buschiix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "env.h"
#include "str.h"

#include <stdio.h>

char	*expander_path(char *cmd, t_env *env)
{
	int		i;
	char	**split;
	char	*s;

	if (!access(cmd, F_OK | X_OK))
		return (cmd);
	s = env_find_value(env, "PATH");
	if (!s)
		return (NULL);
	split = str_split(s, ":");
	i = 0;
	while (split && split[i])
	{
		s = str_join(split[i], cmd, '/');
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
