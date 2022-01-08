/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 19:32:25 by rgeny             #+#    #+#             */
/*   Updated: 2022/01/08 17:37:13 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "env.h"
#include "str.h"
#include "error.h"
#include "print.h"
#include "struct.h"
#include "utils.h"

static int	static_isavailable(char *s, t_data *data)
{
	if (uti_is_valid_var_name(s))
		return (SUCCESS);
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
