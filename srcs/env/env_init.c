/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 19:51:23 by rgeny             #+#    #+#             */
/*   Updated: 2021/12/15 14:31:46 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "str.h"

void	env_init(t_env **env, char *envp[])
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
		env_add(env, env_new(name, value));
		i++;
	}
}
