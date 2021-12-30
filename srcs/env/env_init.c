/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 19:51:23 by rgeny             #+#    #+#             */
/*   Updated: 2021/12/30 15:17:55 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "str.h"
#include "utils.h"
#include <stdlib.h>

static void	static_cpy(t_env **env, char *envp[])
{
	char	*name;
	char	*value;
	int		i;
	int		j;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
			j++;
		name = str_ndup(envp[i], j);
		j++;
		value = str_ndup(&envp[i][j], str_len(&envp[i][j], 0));
		env_new(env, name, value);
		i++;
	}
}

static void	static_actualize(t_env **env, char *cmd)
{
	t_env	*pwd;
	t_env	*node;
	char	*s;
	int		n;

	pwd = env_find(*env, "PWD");
	s = str_join(pwd->value, cmd, '/');
	env_assign(*env, "SHELL", s);
	s = str_ndup(s, str_len(s, 0));
	env_assign(*env, "_", s);
	node = env_find(*env, "SHLVL");
	n = uti_atoi(node->value) + 1;
	s = uti_itoa(n);
	env_assign(*env, "SHLVL", s);
}

void	env_init(t_env **env, char *envp[], char *cmd)
{
	static_cpy(env, envp);
	static_actualize(env, cmd);
}
