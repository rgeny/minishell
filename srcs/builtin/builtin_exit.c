/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 22:00:47 by rgeny             #+#    #+#             */
/*   Updated: 2022/01/06 17:48:27 by buschiix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "str.h"
#include "utils.h"
#include "env.h"
#include "builtin.h"
#include "global.h"
#include "error.h"

static void	static_exit(char **cmd, t_data *data, int ret)
{
	str_free_string(cmd);
	env_del_all(data->env);
	glo_pwd(0, 1);
	exit(ret);
}

static int	static_check_first(char **cmd, t_data *data)
{
	long	ret;

	ret = uti_ato_l(cmd[1]);
	if (uti_isdigit(cmd[1]) || ret == -1)
	{
		perror("minishell: exit");
		static_exit(cmd, data, 2);
	}
	return (ret % 256);
}

int	builtin_exit(char **cmd, t_data *data)
{
	int	ret;
	int	len;

	ret = 0;
	len = str_llen(cmd);
	if (len > 1)
		ret = static_check_first(cmd, data);
	if (len < 3)
		static_exit(cmd, data, ret);
	str_printerr("minishell: exit: too many arguments\n", 0, 0, 0);
	return (BUILTIN_ERR_EXEC);
}
