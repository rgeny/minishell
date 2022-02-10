/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 22:00:47 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/10 11:53:35 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	_free_and_exit(char **cmd, t_data *data, int ret)
{
	free_ast(&data->ast);
//	str_free_list(cmd);
	(void)cmd;
	env_del_all(data->env);
	str_free(&data->pwd);
	exit(ret);
}

static int	_check_first(char **cmd, t_data *data)
{
	long	ret;

	ret = uti_atol(cmd[1]);
	if ((uti_isdigit(cmd[1]) == true && cmd[1][0] != '-')
		|| uti_isdigit(&cmd[1][1]) == true)
	{
		error_print(EXIT, cmd[1], NUMBERED_ARG, ERROR_SYNTAX);
		_free_and_exit(cmd, data, ERROR_SYNTAX);
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
		_free_and_exit(cmd, data, ret);
	return (error_print(EXIT, TOO_MANY_ARGS, NULL, ERROR_EXEC));
}
