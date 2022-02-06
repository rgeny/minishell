/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 19:32:25 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/06 14:29:20 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "env.h"
#include "str.h"
#include "error.h"
#include "print.h"
#include "struct.h"
#include "utils.h"

static int	_isavailable(char *s)
{
	if (uti_is_valid_name(s))
		return (SUCCESS);
	return (error_print("unset: ", s, ": not a valid identifier\n", ERROR_EXEC));
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
		if (!_isavailable(cmd[i]))
		{
			to_del = env_find_var(data->env, cmd[i]);
			if (to_del)
			{
				if (data->env == to_del)
					data->env = &(*to_del->next);
				env_del_one(to_del);
			}
		}
		else
			ret = ERROR_EXEC;
		i++;
	}
	return (ret);
}
