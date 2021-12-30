/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 19:32:25 by rgeny             #+#    #+#             */
/*   Updated: 2021/12/30 19:49:29 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "env.h"

int	env_unset(char **cmd, t_env *env)
{
	int		i;
	t_env	*to_del;

	if (cmd[1])
	{
		i = 1;
		while (cmd[i])
		{
			to_del = env_find(env, cmd[i]);
			if (to_del)
				env_del_one(to_del);
			i++;
		}
		return (0);
	}
	else
	{
		write(2, "unset: not enough arguments\n", 28);
		return (1);
	}
}
