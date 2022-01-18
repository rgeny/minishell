/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 15:08:49 by rgeny             #+#    #+#             */
/*   Updated: 2022/01/18 10:50:11 by buschiix         ###   ########.fr       */
/*   Updated: 2022/01/09 13:33:47 by buschiix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "env.h"
#include "str.h"
#include "utils.h"

static char	*_find_var_value(char *cmd, t_data *data)
{
	t_env	*env;
	char	*name;

	if (cmd[0] == '?')
		return (uti_itoa(data->ret));
	name = str_ndup(cmd, str_len_alnum(cmd));
	env = env_find(data->env, name);
	str_free(name);
	if (env)
		return (str_ndup(env->value, str_len(env->value, 0)));
	return (0);
}

static char	*_switch_name_to_value(char *prev, char *find, char *cmd, int len)
{
	char	*tmp;
	char	*ret;

	if (prev)
	{
		if (find)
			tmp = str_join(prev, find, 0);
		else
			tmp = str_join(prev, &cmd[len], 0);
	}
	else if (find)
		tmp = str_ndup(find, str_len(find, 0));
	else
		tmp = str_ndup(&cmd[len], str_len(&cmd[len], 0));
	ret = str_join(tmp, &cmd[len], 0);
	str_free(tmp);
	str_free(find);
	return (ret);
}

static void	_expand(char **cmd, t_data *data, int i)
{
	int		len;
	char	*prev;
	char	*ret;
	char	*find;

	prev = str_ndup(cmd[0], i);
	len = str_len_alnum(&cmd[0][i + 1]);
	if (cmd[0][i + 1] == '?')
		len++;
	find = _find_var_value(&cmd[0][i + 1], data);
	if (find || len)
	{
		ret = _switch_name_to_value(prev, find, &cmd[0][i + 1], len);
		str_free(cmd[0]);
		cmd[0] = ret;
	}
	str_free(prev);
}

void	expander_var(char **cmd, t_data *data)
{
	int		i;
	int		j;

	i = 0;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			if (cmd[i][j] == '$')
				_expand(&cmd[i], data, j);
			j++;
		}
		i++;
	}
}
