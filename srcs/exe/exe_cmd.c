/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 10:08:26 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/09 12:27:47 by tokino           ###   ########.fr       */
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

void	exe_cmd(t_ast *ast, t_data *data)
{
	// exe_redir(ast->cmd);
	// if (ast->cmd->arg_nb && ast->cmd->args[0] && error_get() == SUCCESS)
	// {
	// 	exe_builtin(ast->cmd->args, &ast->cmd->args[1], data);
	// 	if (g_last_return == -1)
	// 		exe_out_process(ast->cmd, data);
	// }
}
