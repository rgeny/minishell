/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 15:08:49 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/01 14:19:34 by rgeny            ###   ########.fr       */
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
		return (str_dup(env->value));
	return (0);
}

static char	*_switch_name_to_value(char *prev, char *find, char *cmd, int len)
{
	char	*tmp;
	char	*ret;

	ret = 0;
	tmp = 0;
	tmp = str_join(prev, find, 0);
	ret = str_join(tmp, &cmd[len], 0);
	if (!ret)
		ret = uti_calloc(2, 1);
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

void	expander_var(t_carg *cmd, t_data *data)
{
	int		i;

	while (cmd)
	{
		i = 0;
		while (cmd->content[i])
		{
			if (cmd->content[i] == '$')
				_expand(&cmd->content[i], data, i);
			if (cmd->content[i] && cmd->content[i] != '$' || !uti_isalnum(cmd->content[i + 1]))
				i++;
		}
		cmd = cmd->next;
	}
}
