/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 15:08:49 by rgeny             #+#    #+#             */
/*   Updated: 2022/01/07 20:07:47 by buschiix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "env.h"
#include "str.h"
#include "utils.h"

static void	static_expand(char **splt, t_env *env, int i)
{
	t_env	*tmp;
	char	*s;

	while (splt[i])
	{
		tmp = env_find(env, splt[i]);
		if (tmp)
		{
			s = str_ndup(tmp->value, str_len(tmp->value, 0));
			free(splt[i]);
			splt[i] = s;
		}
		else
		{
			s = uti_calloc(5, sizeof(1));
			free(splt[i]);
			splt[i] = s;
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
		free(ret);
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

void	expander_cmd(char **cmd, t_env *env)
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
		if (cmd[i][j])
		{
			splt = str_split(cmd[i], "$");
			static_expand(splt, env, cmd[i][0] != '$');
			join = static_join(splt);
			str_free_string(splt);
			free(cmd[i]);
			cmd[i] = join;
		}
		i++;
	}
	static_move(cmd, i);
}
