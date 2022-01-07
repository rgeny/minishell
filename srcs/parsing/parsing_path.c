/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 22:32:54 by rgeny             #+#    #+#             */
/*   Updated: 2022/01/07 22:42:46 by buschiix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "env.h"
#include "str.h"

void	parsing_path(char **cmd, t_env *env)
{
	int		i;
	char	**split;
	char	*s;

	if (!access(cmd[0], F_OK | X_OK))
		return ;
	env = env_find(env, "PATH");
	if (!env)
		return ;
	split = str_split(env->value, ":");
	i = 0;
	while (split && split[i])
	{
		s = str_join(split[i], cmd[0], '/');
		if (!access(s, F_OK | X_OK))
		{
			free(cmd[0]);
			cmd[0] = s;
			str_free_string(split);
			return ;
		}
		free(s);
		i++;
	}
	str_free_string(split);
}
