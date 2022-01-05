/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 19:51:23 by rgeny             #+#    #+#             */
/*   Updated: 2022/01/05 18:59:36 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "str.h"
#include "utils.h"
#include <stdlib.h>
#include <unistd.h>

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

static void	static_actualize(t_env **env, char *exe)
{
	t_env	*node;
	char	*s;
	char	*s2;
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
	env_new(env, str_ndup("SHLVL", 5), s);
	node = env_find(*env, "PATH");
	if (node)
	{
		if (str_len(exe, 0) > 10)
		{
			s = str_ndup(exe, str_len(exe, 0) - 10);
			s2 = str_join(path, s, '/');
			free(s);
		}
		else
			s2 = str_ndup(path, str_len(path, 0));
		s = str_join(s2, "builtin", '/');
		free(s2);
		env_assign(*env, "PATH", str_join(s, node->value, ':'));
		free(s);
	}
	if (!env_find(*env, "OLDPWD"))
		env_new(env, str_ndup("OLDPWD", str_len("OLDPWD", 0)), 0);
}

void	env_init(t_env **env, char *envp[], char *exe)
{
	static_cpy(env, envp);
	static_actualize(env, exe);
}
