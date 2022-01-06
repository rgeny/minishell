/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 18:35:26 by rgeny             #+#    #+#             */
/*   Updated: 2022/01/06 18:20:10 by buschiix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "env.h"
#include "str.h"
#include "error.h"

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
	t_data	data;

	data.env = env;
	data.pwd = 0;
	cpy = env_switch(&data, 1);
	static_sort(cpy);
	i = 0;
	while (cpy[i])
	{
		if (cpy[i] && (cpy[i][0] != '_' || cpy[i][1] != '='))
			printf("export %s\n", cpy[i]);
		i++;
	}
	str_free_string(cpy);
	return (SUCCESS);
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
			return (BUILTIN_ERR_EXEC);
		}
		j++;
	}
	var = str_split_first(cmd[0], '=');
	env_new(env, str_ndup(var[0], str_len(var[0], 0)),
		str_ndup(var[1], str_len(var[1], 0)));
	str_free_string(var);
	return (SUCCESS);
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
		ret = SUCCESS;
		while (cmd[i])
		{
			if (static_isdigitchar(cmd[i][0]) == 1)
				ret |= static_new(&cmd[i], env);
			else
			{
				ret = BUILTIN_ERR_EXEC;
				str_printerr("minishell: export: '", cmd[i],
					"': not a valid identifier\n", 0);
			}
			i++;
		}
	}
	return (ret);
}
