/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 19:51:23 by rgeny             #+#    #+#             */
/*   Updated: 2021/12/30 20:34:51 by rgeny            ###   ########.fr       */
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
	printf("%s\n", pwd->value);
	if (pwd)
	{
		s = str_join(pwd->value, cmd, '/');
		env_assign(*env, "SHELL", s);
	}
	s = str_ndup(s, str_len(s, 0));
	env_assign_force(*env, "_", s);
	node = env_find(*env, "SHLVL");
	if (node)
	{
		n = uti_atoi(node->value) + 1;
		s = uti_itoa(n);
	}
	else
		s = uti_itoa(1);
	env_assign_force(*env, "SHLVL", s);
	s = str_ndup(BUILTIN_PATH, str_len(BUILTIN_PATH, 0));
	node = env_find(*env, "PATH");
	if (node)
		env_assign(*env, "PATH", str_join(s, node->value, ':'));
	free(s);
}

void	env_init(t_env **env, char *envp[], char *cmd)
{
	static_cpy(env, envp);
	static_actualize(env, cmd);
}
