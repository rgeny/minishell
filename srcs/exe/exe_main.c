/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 14:14:36 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/09 12:18:03 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/wait.h>
#include <error.h>
#include "struct.h"
#include "exe.h"
#include "minishell_signal.h"

static void	_wait_all(t_node *cmd, t_data *data)
{
	if (!cmd)
		return ;
	if (cmd->type == E_NODE_TYPE_COMMAND)
	{
		if (cmd->cmd->pid && waitpid(cmd->cmd->pid, &g_last_return, 0) != -1)
		{
			if (WIFSIGNALED(g_last_return))
				g_last_return = WTERMSIG(g_last_return) + 128;
			else
				g_last_return = WEXITSTATUS(g_last_return);
		}
	}
	_wait_all(cmd->left, data);
	_wait_all(cmd->right, data);
}

void	exe_main(t_node *cmd, t_data *data)
{
	if (cmd->type == E_NODE_TYPE_PIPE)
		exe_pipe(cmd, data);
	else if (cmd->type == E_NODE_TYPE_COMMAND)
		exe_cmd(cmd, data);
	else if (cmd->type == E_NODE_TYPE_AND)
	{
		exe_main(cmd->left, data);
		if (g_last_return == SUCCESS)
			exe_main(cmd->right, data);
	}
	else if (cmd->type == E_NODE_TYPE_OR)
	{
		exe_main(cmd->left, data);
		if (g_last_return != SUCCESS)
			exe_main(cmd->right, data);
	}
	_wait_all(cmd, data);
	signal_current();
}
