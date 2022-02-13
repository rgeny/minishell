/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 10:08:26 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/13 12:20:14 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

void	exe_cmd(t_ast *ast, t_data *data)
{
	char	**args;
	int		arg_n;

	arg_n = 0;
	args = NULL;
	exe_redir(ast->cmd->redirections, ast->cmd->fd_heredoc, data);
	if (!is_error())
	{
		expand_args(ast->cmd, ast->cmd->cargs, data, &arg_n);
		args = carg_switch_to_list(ast->cmd->cargs, arg_n);
	}
	if (!is_error() && arg_n && args[0])
	{
		exe_builtin(args, &args[1], data);
		if (g_last_return == -1)
			exe_out_process(ast->cmd, args, data);
	}
	if (is_error())
		g_last_return = error_get();
	close_fd(&data->pipefd[0], STDIN_FILENO);
	close_fd(&data->pipefd[1], STDOUT_FILENO);
	ast->cmd->last_return = g_last_return;
	str_free_list(&args);
	error_reset();
}
