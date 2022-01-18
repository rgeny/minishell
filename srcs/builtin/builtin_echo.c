/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 18:20:42 by rgeny             #+#    #+#             */
/*   Updated: 2022/01/18 19:04:31 by buschiix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "str.h"
#include "builtin.h"
#include "error.h"

static int	_check_flag(char **cmd)
{
	int	i;
	int	j;

	i = 1;
	while (cmd[i])
	{
		if (cmd[i][0] == '-')
		{
			j = 1;
			while (cmd[i][j] == 'n')
				j++;
			if (cmd[i][j])
				return (i);
		}
		else
			return (i);
		i++;
	}
	return (i);
}

int	builtin_echo(char **cmd)
{
	int	ret;
	int	i;

	ret = _check_flag(cmd);
	i = ret;
	while (cmd[i])
	{
		write(1, cmd[i], str_len(cmd[i]));
		i++;
		if (cmd[i] && cmd[i][0] && cmd[i - 1][0])
			write(1, " ", 1);
	}
	if (ret == 1)
		write(1, "\n", 1);
	return (SUCCESS);
}
