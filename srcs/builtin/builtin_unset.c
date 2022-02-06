/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 19:32:25 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/06 15:36:18 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_unset(char **cmd, t_data *data)
{
	while (*cmd != NULL)
	{
		if (uti_is_valid_name(*cmd) == true)
			env_del_one(&data->env, *cmd);
		else
			error_print(UNSET, *cmd, BAD_IDENTIFIER, ERROR_EXEC);
		cmd++;
	}
	return (error_get());
}
