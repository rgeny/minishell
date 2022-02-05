/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 19:38:47 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/05 18:31:28 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "env.h"
#include "str.h"
#include "error.h"

void	exe_builtin(char **cmd, char **args, t_data *data)
{
	if (!str_cmp(cmd[0], "export"))
		g_last_return = builtin_export(cmd, data);
	else if (!str_cmp(cmd[0], "unset"))
		g_last_return = builtin_unset(cmd, data);
	else if (!str_cmp(cmd[0], "exit"))
		g_last_return = builtin_exit(cmd, data);
	else if (!str_cmp(cmd[0], "cd"))
		g_last_return = builtin_cd(args, data);
	else if (!str_cmp(cmd[0], "echo"))
		g_last_return = builtin_echo(args);
	else if (!str_cmp(cmd[0], "env"))
		g_last_return = builtin_env(env_switch(data, 0));
	else if (!str_cmp(cmd[0], "pwd"))
		g_last_return = builtin_pwd(cmd, data);
	else
		g_last_return = -1;
}
