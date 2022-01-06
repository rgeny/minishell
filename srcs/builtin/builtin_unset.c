/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 19:32:25 by rgeny             #+#    #+#             */
/*   Updated: 2022/01/06 22:03:19 by buschiix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "env.h"
#include "str.h"
#include "error.h"
#include "print.h"
#include "struct.h"

static int	static_isdigitchar(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
		return (1);
	if (c >= '0' && c <= '9')
		return (2);
	return (0);
}

static int	static_isavailable(char *s, t_data *data)
{
	int	i;

	if (static_isdigitchar(s[0]) == 1)
	{
		i = 1;
		while (s[i])
		{
			if (!static_isdigitchar(s[i]))
			{
				print_error("unset: ", s, ": not a valid identifier\n", data);
				return (BUILTIN_ERR_EXEC);
			}
			i++;
		}
		return (SUCCESS);
	}
	else
	{
		print_error("unset: ", s, ": not a valid identifier\n", data);
		return (BUILTIN_ERR_EXEC);
	}
}

int	builtin_unset(char **cmd, t_data *data)
{
	int		i;
	t_env	*to_del;
	int		ret;

	ret = SUCCESS;
	i = 1;
	while (cmd[i])
	{
		if (!static_isavailable(cmd[i], data))
		{
			to_del = env_find(data->env, cmd[i]);
			if (to_del)
			{
				if (data->env == to_del)
					data->env = &(*to_del->next);
				env_del_one(to_del);
			}
		}
		else
			ret = BUILTIN_ERR_EXEC;
		i++;
	}
	return (ret);
}
