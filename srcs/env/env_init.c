/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 19:51:23 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/06 17:04:58 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static void	_cpy(t_env **env, char *envp[])
{
	int		i;
	int		len;

	i = 0;
	while (envp[i] != NULL)
	{
		len = str_clen(envp[i], '=');
		env_new(env, str_ndup(envp[i], len), str_dup(&envp[i][len + 1]));
		i++;
	}
}

static void	_actualize(t_env **env)
{
	char	*tmp;
	int		n;

	tmp = getcwd(NULL, 0);
	env_new(env, str_dup("_"), str_dup(tmp));
	env_new(env, str_dup(ENV_PWD), tmp);
	tmp = env_find_val(*env, ENV_SHLVL);
	n = uti_atoi(tmp) + 1;
	tmp = uti_itoa(n);
	env_new(env, str_dup(ENV_SHLVL), tmp);
	tmp = str_dup(env_find_val(*env, ENV_OLDPWD));
	env_new(env, str_dup(ENV_OLDPWD), tmp);
}

void	env_init(t_env **env, char *envp[])
{
	_cpy(env, envp);
	_actualize(env);
}
