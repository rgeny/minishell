/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 19:38:47 by rgeny             #+#    #+#             */
/*   Updated: 2022/01/06 17:45:25 by buschiix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "str.h"

int	exe_builtin(char **cmd, t_data *data)
{
	int	ret;

	ret = -1;
	if (!str_cmp(cmd[0], "export"))
		ret = builtin_export(cmd, &data->env);
	else if (!str_cmp(cmd[0], "unset"))
		ret = builtin_unset(cmd, &data->env);
	else if (!str_cmp(cmd[0], "exit"))
		ret = builtin_exit(cmd, data);
	else if (!str_cmp(cmd[0], "cd"))
		ret = builtin_cd(cmd, data);
	return (ret);
}
