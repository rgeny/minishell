/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 15:08:49 by rgeny             #+#    #+#             */
/*   Updated: 2022/01/08 21:14:01 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "env.h"
#include "str.h"
#include "utils.h"

static void	static_expand(char **splt, t_data *data, int i)
{
	t_env	*tmp;
	char	*s;
	int		len;
	char	*s2;

	while (splt[i])
	{
		len = str_len_alnum(splt[i]);
		s = str_ndup(splt[i], len);
		tmp = env_find(data->env, s);
		free(s);
		if (tmp)
		{
			s = str_ndup(tmp->value, str_len(tmp->value, 0));
			s2 = str_ndup(&splt[i][len], str_len(&splt[i][len], 0));
			str_free(splt[i]);
			splt[i] = str_join(s, s2, 0);
			str_free(s);
			str_free(s2);
		}
		else if (splt[i][0] == '?')
		{
			s = uti_itoa(data->ret);
			s2 = str_ndup(&splt[i][1], str_len(&splt[i][1], 0));
			str_free(splt[i]);
			splt[i] = str_join(s, s2, 0);
			str_free(s);
			str_free(s2);
		}
		else
		{
			str_free(splt[i]);
			splt[i] = uti_calloc(1, sizeof(char));;
		}
		i++;
	}
}

static char	*static_join(char **splt)
{
	int		i;
	char	*ret;
	char	*tmp;

	i = 1;
	ret = str_ndup(splt[0], str_len(splt[0], 0));
	while (splt[i])
	{
		tmp = str_join(ret, splt[i], 0);
		str_free(ret);
		ret = tmp;
		i++;
	}
	return (ret);
}

static void	static_move(char **cmd, int sz)
{
	int	i;
	int	j;

	i = 0;
	while (i < sz)
	{
		if (!cmd[i])
		{
			j = i + 1;
			while (j < sz && !cmd[j])
				j++;
			if (cmd[j])
			{
				cmd[i] = cmd[j];
				cmd[j] = 0;
			}
		}
		i++;
	}
}

void	expander_cmd(char **cmd, t_data *data)
{
	int		i;
	int		j;
	char	**splt;
	char	*join;

	i = 0;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j] && cmd[i][j] != '$')
			j++;
		if (cmd[i][j] && (uti_isalnum(cmd[i][j + 1]) || cmd[i][j + 1] == '?'))
		{
			splt = str_split(cmd[i], "$");
			static_expand(splt, data, cmd[i][0] != '$');
			join = static_join(splt);
			str_free_list(splt);
			str_free(cmd[i]);
			cmd[i] = join;
		}
		i++;
	}
	static_move(cmd, i);
}
