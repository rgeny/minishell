/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 19:32:25 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/10 18:15:00 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_unset(char **cmd, t_data *data)
{
	while (*cmd != NULL)
	{
		if (is_valid_name(*cmd))
			env_del_one(&data->env, *cmd);
		else
			error_print(UNSET, *cmd, BAD_IDENTIFIER, ERROR_EXEC);
		cmd++;
	}
	return (error_get());
}
