/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 18:35:26 by rgeny             #+#    #+#             */
/*   Updated: 2022/01/01 11:14:08 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "str.h"
#include <stdio.h>
#include <stdlib.h>

static void	static_sort(char **s)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (s[i])
	{
		j = i + 1;
		while (s[j])
		{
			if (str_cmp(s[i], s[j]) > 0)
			{
				tmp = s[i];
				s[i] = s[j];
				s[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	static_print(t_env *env)
{
	char	**cpy;
	int		i;

	cpy = env_switch(&env, 1);
	static_sort(cpy);
	i = 0;
	while (cpy[i])
	{
		if (cpy[i] && (cpy[i][0] != '_' || cpy[i][1] != '='))
			printf("export %s\n", cpy[i]);
		i++;
	}
	str_free_string(cpy);
}

static void	static_new(char **cmd, t_env **env)
{
	int		i;
	char	**var;

	i = 1;
	while (cmd[i])
	{
		var = str_split(cmd[i], "=");
		env_new(env, str_ndup(var[0], str_len(var[0], 0)),
			str_ndup(var[1], str_len(var[1], 0)));
		str_free_string(var);
		i++;
	}
}

int	builtin_export(char **cmd, t_env **env)
{
	if (!cmd[1])
		static_print(*env);
	else
		static_new(cmd, env);
	return (0);
}
