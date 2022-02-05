/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 18:20:42 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/05 20:56:19 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	_check_flag(char **cmd)
{
	int	i;
	int	j;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i][0] != '-')
			return (i);
		j = str_first_dif(&cmd[i][1], 'n') + 1;
		if (cmd[i][j])
			return (i);
		i++;
	}
	return (i);
}

int	builtin_echo(char **cmd)
{
	bool	flag;
	int		i;

	i = _check_flag(cmd);
	flag = (bool)i;
	while (cmd[i])
	{
		if (write(1, cmd[i], str_len(cmd[i])) && cmd[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (flag == false)
		write(1, "\n", 1);
	return (SUCCESS);
}
