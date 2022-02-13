/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_out_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 17:59:16 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/13 15:32:43 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

static void	_son(char **cmd, t_data *data)
{
	char	**env_cpy;
	char	*path;

	signal_fork();
	env_cpy = env_switch(data, 0);
	str_free(&data->pwd);
	path = expand_path(cmd[0], data->env);
	if (path != NULL)
		execve(path, cmd, env_cpy);
	error_print(cmd[0], CMD_NOT_FOUND, NULL, EXECVE_FAIL);
	str_free_list(&cmd);
	str_free_list(&env_cpy);
	str_free(&path);
	env_del_all(data->env);
	free_ast(&data->ast);
	exit(EXECVE_FAIL);
}

void	exe_out_process(t_command *cmd, char **args, t_data *data)
{
	cmd->pid = fork();
	if (cmd->pid == 0)
	{
		dup_and_close(&data->pipefd[0], STDIN_FILENO);
		dup_and_close(&data->pipefd[1], STDOUT_FILENO);
		close_fd(&data->fd_in, STDIN_FILENO);
		_son(args, data);
	}
	signal_ignore();
}
