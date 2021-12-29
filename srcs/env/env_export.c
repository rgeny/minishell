/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 18:35:26 by rgeny             #+#    #+#             */
/*   Updated: 2021/12/29 22:56:44 by rgeny            ###   ########.fr       */
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

static void	static_print(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] && (s[i][0] != '_' || s[i][1] != '='))
			printf("%s\n", s[i]);
		i++;
	}
}

int	env_export(char **cmd, t_env **env)
{
	char	**cpy;

	cpy = env_switch(*env, 1);
	if (!cmd[1])
	{
		static_sort(cpy);
		static_print(cpy);
	}
	else
		env_new(env, cmd[1], cmd[2]);
	for (int i = 0; cpy[i]; i++)
		free(cpy[i]);
	free(cpy);
	for (int i = 0; cmd[i]; i++)
		free(cmd[i]);
	free(cmd);
	env_del_all(*env);
	return (0);
}
