/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 10:08:26 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/08 20:05:49 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "exe.h"
#include <stdio.h>
#include "error.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "str.h"

void	exe_cmd(t_node *cmd, t_data *data)
{
/*	exe_redir(cmd->command);
	if (cmd->command->arg_nb && cmd->command->args[0] && error_get() == SUCCESS)
	{
		exe_builtin(cmd->command->args, &cmd->command->args[1], data);
		if (g_last_return == -1)
			exe_out_process(cmd->command, data);
	}*/
}
