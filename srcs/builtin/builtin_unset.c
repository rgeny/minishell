/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 19:32:25 by rgeny             #+#    #+#             */
/*   Updated: 2022/01/01 15:32:16 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "env.h"
#include "str.h"

static int	static_isdigitchar(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
		return (1);
	if (c >= '0' && c <= '9')
		return (2);
	return (0);
}

static int	static_isavailable(char *s)
{
	int	i;

	if (static_isdigitchar(s[0]) == 1)
	{
		i = 1;
		while (s[i])
		{
			if (!static_isdigitchar(s[i]))
			{
				str_printerr("bash: unset: '", s,
					"': not a valid identifier\n", 0);
				return (1);
			}
			i++;
		}
		return (0);
	}
	else
	{
		str_printerr("bash: unset: '", s, "': not a valid identifier\n", 0);
		return (1);
	}
}

int	builtin_unset(char **cmd, t_env **env)
{
	int		i;
	t_env	*to_del;
	int		ret;

	ret = 0;
	i = 1;
	while (cmd[i])
	{
		if (!static_isavailable(cmd[i]))
		{
			to_del = env_find(*env, cmd[i]);
			if (to_del)
			{
				if (*env == to_del)
					*env = &(*to_del->next);
				env_del_one(to_del);
			}
		}
		else
			ret = 1;
		i++;
	}
	return (ret);
}
