/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 10:08:26 by rgeny             #+#    #+#             */
/*   Updated: 2022/01/28 10:39:44 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "exe.h"
#include <stdio.h>
void	exe_cmd(t_node *cmd, t_data *data)
{
	exe_redir(cmd->command);
	if (cmd->command->arg_nb)
	{
		exe_builtin(cmd->command->args, data);
		if (data->ret == -1)
			exe_out_process(cmd->command->args, data);
	}
}
