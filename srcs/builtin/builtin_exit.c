/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 22:00:47 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/05 19:44:31 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "str.h"
#include "utils.h"
#include "env.h"
#include "builtin.h"
#include "error.h"
#include "print.h"

static void	_ft_exit(char **cmd, t_data *data, int ret)
{
	str_free_list(cmd);
	env_del_all(data->env);
	str_free(data->pwd);
	exit(ret);
}

static int	_check_first(char **cmd, t_data *data)
{
	long	ret;

	ret = uti_ato_l(cmd[1]);
	if ((uti_isdigit(cmd[1]) && cmd[1][0] != '-')
		|| (cmd[1][1] && uti_isdigit(&cmd[1][1])))
	{
		error_print(EXIT, cmd[1], NUMBERED_ARG, ERROR_SYNTAX);
		_ft_exit(cmd, data, ERROR_SYNTAX);
	}
	return ((unsigned char)ret);
}

int	builtin_exit(char **cmd, t_data *data)
{
	int	ret;
	int	len;

	ret = 0;
	len = str_llen(cmd);
	if (len > 1)
		ret = _check_first(cmd, data);
	if (len < 3)
		_ft_exit(cmd, data, ret);
	return (error_print(EXIT, TOO_MANY_ARGS, NULL, ERROR_EXEC));
}
