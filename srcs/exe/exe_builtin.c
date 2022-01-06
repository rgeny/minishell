/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 19:38:47 by rgeny             #+#    #+#             */
/*   Updated: 2022/01/06 21:34:17 by buschiix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "str.h"

void	exe_builtin(char **cmd, t_data *data)
{
	if (!str_cmp(cmd[0], "export"))
		data->ret = builtin_export(cmd, data);
	else if (!str_cmp(cmd[0], "unset"))
		data->ret = builtin_unset(cmd, data);
	else if (!str_cmp(cmd[0], "exit"))
		data->ret = builtin_exit(cmd, data);
	else if (!str_cmp(cmd[0], "cd"))
		data->ret = builtin_cd(cmd, data);
	else
		data->ret = -1;
}
