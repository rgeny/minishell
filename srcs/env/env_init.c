/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 19:51:23 by rgeny             #+#    #+#             */
/*   Updated: 2022/01/09 16:50:15 by buschiix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "str.h"
#include "utils.h"
#include <stdlib.h>
#include <unistd.h>

#include <stdio.h>

static void	static_cpy(t_env **env, char *envp[])
{
	char	*name;
	char	*value;
	int		i;
	int		j;

	i = 0;
	while (envp[i])
	{
		j = str_len(envp[i], '=');
		name = str_ndup(envp[i], j);
		j++;
		if (name)
		{
			value = str_ndup(&envp[i][j], str_len(&envp[i][j], 0));
			env_new(env, name, value);
		}
		i++;
	}
}

static void	static_actualize(t_env **env)
{
	t_env	*node;
	char	*s;
	int		n;
	char	path[PATH_CHAR_MAX + 1];

	getcwd(path, PATH_CHAR_MAX + 1);
	env_new(env, str_ndup("PWD", 3), str_ndup(path, str_len(path, 0)));
	node = env_find(*env, "SHLVL");
	if (node && node->value)
		n = uti_ato_i(node->value) + 1;
	else
		n = 1;
	s = uti_itoa(n);
	if (s)
		env_new(env, str_ndup("SHLVL", 5), s);
	if (!env_find(*env, "OLDPWD"))
		env_new(env, str_ndup("OLDPWD", str_len("OLDPWD", 0)), 0);
}

void	env_init(t_env **env, char *envp[])
{
	static_cpy(env, envp);
	static_actualize(env);
}
