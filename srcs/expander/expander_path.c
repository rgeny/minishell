/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 22:32:54 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/10 04:28:22 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static char	*_find_path(char *cmd, char **path_list)
{
	char	*path_cmd;

	while (*path_list)
	{
		path_cmd = str_join(*path_list, cmd, '/');
		if (access(path_cmd, F_OK | X_OK) == SUCCESS)
			return (path_cmd);
		path_list++;
	}
	return (NULL);
}

char	*expand_path(char *cmd, t_env *env)
{
	char	**path_list;
	char	*path_var;
	char	*path_cmd;

	if (access(cmd, F_OK | X_OK) == SUCCESS)
		return (cmd);
	path_var = env_find_val(env, "PATH");
	if (path_var == NULL)
		return (NULL);
	path_list = str_split(path_var, ":");
	if (path_list == NULL)
		return (NULL);
	path_cmd = _find_path(cmd, path_list);
	str_free_list(path_list);
	return (path_cmd);
}
