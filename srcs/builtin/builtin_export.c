/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 18:35:26 by rgeny             #+#    #+#             */
/*   Updated: 2022/01/01 15:15:14 by rgeny            ###   ########.fr       */
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

static int	static_print(t_env *env)
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
	return (0);
}

static int	static_isdigitchar(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
		return (1);
	if (c >= '0' && c <= '9')
		return (2);
	return (0);
}

static int	static_new(char **cmd, t_env **env)
{
	int		j;
	char	**var;

	j = 0;
	while (cmd[0][j] && cmd[0][j] != '=')
	{
		if (!static_isdigitchar(cmd[0][j]))
		{
			str_printerr("minishell: export: '", cmd[0],
				"': not a valid identifier\n", 0);
			return (1);
		}
		j++;
	}
	var = str_split(cmd[0], "=");
	env_new(env, str_ndup(var[0], str_len(var[0], 0)),
		str_ndup(var[1], str_len(var[1], 0)));
	str_free_string(var);
	return (0);
}

int	builtin_export(char **cmd, t_env **env)
{
	int	i;
	int	ret;

	ret = 0;
	if (!cmd[1])
		return (static_print(*env));
	else
	{
		i = 1;
		ret = 0;
		while (cmd[i])
		{
			if (static_isdigitchar(cmd[i][0]) == 1)
				ret |= static_new(&cmd[i], env);
			else
			{
				ret = 1;
				str_printerr("minishell: export: '", cmd[i],
					"': not a valid identifier\n", 0);
			}
			i++;
		}
	}
	return (ret);
}
/*	int		i;
	int		j;
	int		ret;
	char	**var;

	i = 1;
	ret = 0;
	while (cmd[i])
	{
		j = 0;
		if (static_isdigitchar(cmd[i][j]) == 1)
		{
			while (cmd[i][j] && cmd[i][j] != '=')
			{
				if (!static_isdigitchar(cmd[i][j]))
				{
					str_printerr("minishell: export: '", cmd[i],
						"': not a valid identifier\n", 0);
					ret = 1;
					break ;
				}
				j++;
			}
			var = str_split(cmd[i], "=");
			env_new(env, str_ndup(var[0], str_len(var[0], 0)),
				str_ndup(var[1], str_len(var[1], 0)));
			str_free_string(var);
		}
		else
		{
			ret = 1;
			str_printerr("minishell: export: '", cmd[i],
				"': not a valid identifier\n", 0);
		}
		i++;
	}
	return (ret);*/
