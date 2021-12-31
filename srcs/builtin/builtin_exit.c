/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 22:00:47 by rgeny             #+#    #+#             */
/*   Updated: 2021/12/31 23:44:05 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "str.h"
#include "utils.h"
#include "env.h"
#include "builtin.h"

static void	static_exit(char **cmd, t_env *env, int ret)
{
	str_free_string(cmd);
	env_del_all(env);
	exit(ret);
}

static int	static_check_first(char **cmd, t_env *env)
{
	long	ret;

	ret = uti_ato_l(cmd[1]);
	if (uti_isdigit(cmd[1]) || ret == -1)
	{
		str_printerr("minishell: exit: ", cmd[1],
			": numeric argument required\n", 0);
		static_exit(cmd, env, 2);
	}
	return (ret % 256);
}

int	builtin_exit(char **cmd, t_env *env)
{
	int	ret;
	int	len;

	ret = 0;
	len = str_llen((const char **)cmd);
	if (len > 1)
		ret = static_check_first(cmd, env);
	if (len < 3)
		static_exit(cmd, env, ret);
	str_printerr("minishell: exit: too many arguments\n", 0, 0, 0);
	return (1);
}
