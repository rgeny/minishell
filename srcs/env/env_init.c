/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 19:51:23 by rgeny             #+#    #+#             */
/*   Updated: 2022/01/28 18:43:57 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "str.h"
#include "utils.h"
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>

static void	_cpy(t_env **env, char *envp[])
{
	char	*name;
	char	*value;
	int		i;
	int		j;

	i = 0;
	while (envp[i])
	{
		j = str_clen(envp[i], '=');
		name = str_ndup(envp[i], j);
		j++;
		if (name)
		{
			value = str_dup(&envp[i][j]);
			env_new(env, name, value);
		}
		i++;
	}
}

static void	_actualize(t_env **env)
{
	t_env	*node;
	char	*s;
	int		n;
	char	path[PATH_MAX + 1];

	getcwd(path, PATH_MAX + 1);
	env_new_(path, env);
	env_new(env, str_dup("PWD"), str_dup(path));
	node = env_find(*env, "SHLVL");
	if (node && node->value)
		n = uti_ato_i(node->value) + 1;
	else
		n = 1;
	s = uti_itoa(n);
	if (s)
		env_new(env, str_dup("SHLVL"), s);
	if (!env_find(*env, "OLDPWD"))
		env_new(env, str_dup("OLDPWD"), 0);
}

void	env_init(t_env **env, char *envp[])
{
	_cpy(env, envp);
	_actualize(env);
}
