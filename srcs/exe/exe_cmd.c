/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 10:08:26 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/09 12:18:12 by tokino           ###   ########.fr       */
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
/*	exe_redir(cmd->cmd);
	if (cmd->cmd->arg_nb && cmd->cmd->args[0] && error_get() == SUCCESS)
	{
		exe_builtin(cmd->cmd->args, &cmd->cmd->args[1], data);
		if (g_last_return == -1)
			exe_out_process(cmd->cmd, data);
	}*/
}
