/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 18:35:26 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/01 17:03:50 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "env.h"
#include "str.h"
#include "error.h"
#include "print.h"
#include "struct.h"
#include "utils.h"

static int	_print(t_env *env)
{
	char	**cpy;
	int		i;
	t_data	data;

	data.env = env;
	data.pwd = 0;
	cpy = env_switch(&data, 1);
	if (cpy)
	{
		uti_quicksort(0, str_llen(cpy) - 1, cpy);
		i = 0;
		while (cpy[i])
		{
			if (cpy[i] && (cpy[i][0] != '_' || cpy[i][1] != '='))
			{
				write(1, "export ", 7);
				write(1, cpy[i], str_len(cpy[i]));
				write(1, "\n", 1);
			}
			i++;
		}
	}
	str_free_list(cpy);
	return (SUCCESS);
}

static int	_new(char **cmd, t_data *data)
{
	char	**var;

	var = str_split_first(cmd[0], '=');
	env_new(&data->env, str_dup(var[0]), str_dup(var[1]));
	str_free_list(var);
	return (SUCCESS);
}

int	builtin_export(char **cmd, t_data *data)
{
	int	i;
	int	ret;

	ret = 0;
	if (!cmd[1])
		return (_print(data->env));
	else
	{
		i = 1;
		ret = SUCCESS;
		while (cmd[i])
		{
			if (uti_is_valid_var_name(cmd[i]))
				ret |= _new(&cmd[i], data);
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
