/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 10:08:26 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/03 12:45:47 by buschiix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "exe.h"
#include <stdio.h>
#include "error.h"
#include <unistd.h>

void	exe_cmd(t_node *cmd, t_data *data)
{
	exe_redir(cmd->command);
	if (cmd->command->arg_nb && cmd->command->args[0])
	{
		exe_builtin(cmd->command->args, data);
		if (g_last_return == -1)
			exe_out_process(cmd->command, data);
	}
}
