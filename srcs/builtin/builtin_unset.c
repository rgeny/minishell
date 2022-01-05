/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 19:32:25 by rgeny             #+#    #+#             */
/*   Updated: 2022/01/05 15:00:51 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "env.h"
#include "str.h"
#include "error.h"

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
				return (BUILTIN_ERR_EXEC);
			}
			i++;
		}
		return (SUCCESS);
	}
	else
	{
		str_printerr("bash: unset: '", s, "': not a valid identifier\n", 0);
		return (BUILTIN_ERR_EXEC);
	}
}

int	builtin_unset(char **cmd, t_env **env)
{
	int		i;
	t_env	*to_del;
	int		ret;

	ret = SUCCESS;
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
			ret = BUILTIN_ERR_EXEC;
		i++;
	}
	return (ret);
}
