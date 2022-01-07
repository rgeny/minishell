/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 18:35:26 by rgeny             #+#    #+#             */
/*   Updated: 2022/01/07 01:03:46 by buschiix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "env.h"
#include "str.h"
#include "error.h"
#include "print.h"
#include "struct.h"

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
		{
			write(1, "export ", 7);
			write(1, cpy[i], str_len(cpy[i], 0));
			write(1, "\n", 1);
		}
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

static int	static_new(char **cmd, t_data *data)
{
	int		j;
	char	**var;

	j = 0;
	while (cmd[0][j] && cmd[0][j] != '=')
	{
		if (!static_isdigitchar(cmd[0][j]))
		{
			print_error("export: ", cmd[0], ": not a valid identifier\n", data);
			return (BUILTIN_ERR_EXEC);
		}
		j++;
	}
	var = str_split_first(cmd[0], '=');
	env_new(&data->env, str_ndup(var[0], str_len(var[0], 0)),
		str_ndup(var[1], str_len(var[1], 0)));
	str_free_string(var);
	return (SUCCESS);
}

int	builtin_export(char **cmd, t_data *data)
{
	int	i;
	int	ret;

	ret = 0;
	if (!cmd[1])
		return (static_print(data->env));
	else
	{
		i = 1;
		ret = SUCCESS;
		while (cmd[i])
		{
			if (static_isdigitchar(cmd[i][0]) == 1)
				ret |= static_new(&cmd[i], data);
			else
			{
				ret = BUILTIN_ERR_EXEC;
				print_error("export: ", cmd[i],
					": not a valid identifier\n", data);
			}
			i++;
		}
	}
	return (ret);
}
