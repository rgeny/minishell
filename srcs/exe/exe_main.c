/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 14:14:36 by rgeny             #+#    #+#             */
/*   Updated: 2022/01/27 18:35:24 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "struct.h"
#include "exe.h"

static void	_print(t_node cmd)
{
	int	i;
	
	if (cmd.type == E_NODE_TYPE_COMMAND)
	{
		printf ("CMD : ");
		i = 0;
		while (cmd.command->args[i])
		{
			printf("%s\n", cmd.command->args[i]);
			i++;
		}
		printf("\nRedir : ");
		if (cmd.command->redir_nb)
		{
			i = 0;
			while (i < cmd.command->redir_nb)
			{
				printf("%d:%s(%d) ", i, cmd.command->redirections[i].path, cmd.command->redirections[i].type);
				i++;
			}
		}
		else
			printf("none");
	}
	else
	{
		printf("PIPE");
	}
	printf("\n\n");
}

void	_exe_redir(t_redir *redir, int size, int in, int out)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (i < size)
	{
		if (redir[i].type == E_REDIR_TYPE_HEREDOC)
			j = i;
		i++;
	}

	i = 0;
	while (i < size)
	{
		if (redir[i].type == E_REDIR_TYPE_STDIN)
		{
			if (in != 1)
				close(in);
			in = open(redir[i].path, O_RDONLY);
		}
		else if (redir[i].type == E_REDIR_TYPE_STDOUT && i > j)
		{
			if (out != 0)
				close(out);
			out = open(redir[i].path, O_WRONLY);
		}
		i++;
	}
	if (in != 0)
	{
		dup2(in, 0);
		close(in);
	}
	if (out != 1)
	{
		dup2(out, 1);
		close(out);
	}
	printf("in : %d\nout : %d\n", in, out);
}

void	_exe_cmd(t_command *cmd, t_data *data)
{
	exe_builtin(cmd->args, data);
	if (data->ret == -1)
		exe_out_process(cmd->args, data);
}

void	exe_main(t_node *cmd, t_data * data)
{
	int	pipefd[2];
	int	fd;

	pipe(pipefd);
	if (!cmd)
		return ;
	if (cmd->type == E_NODE_TYPE_PIPE)
	{
		fd = dup(1);
		dup2(pipefd[1], 1);
	}
	exe_main(cmd->left, data);
	if (cmd->type == E_NODE_TYPE_COMMAND)
	{
		_exe_cmd(cmd->command, data);
		_exe_redir(cmd->command->redirections, cmd->command->redir_nb, cmd->command->fd_in, cmd->command->fd_out);
	}
	else if (cmd->type == E_NODE_TYPE_PIPE)
	{
		dup2(fd, 1);
		fd = dup(0);
		close(pipefd[1]);
		dup2(pipefd[0], 0);
	}
	exe_main(cmd->right, data);
	if (cmd->type == E_NODE_TYPE_PIPE)
	{
		dup2(fd, 0);
	}
}
