/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 16:54:37 by rgeny             #+#    #+#             */
/*   Updated: 2022/01/27 18:13:32 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "expander.h"

static void	_heredoc(t_data *data, t_command *cmd)
{
	int	i = 0;
	int	fd;

	cmd->fd_in = 0;
	cmd->fd_out = 1;
	i = 0;
	while (i < cmd->redir_nb)
	{
		if (cmd->redirections[i].type == E_REDIR_TYPE_HEREDOC)
		{
			fd = expander_heredoc(cmd->redirections[i].path, data);
			if (cmd->fd_in)
				close(cmd->fd_in);
			cmd->fd_in = fd;
		}
		i++;
	}
}

static void	_asterisk(char **cmd)
{
	char	*tmp;
	int		i;

	tmp = 0;
	i = 0;
	while (cmd[i])
	{
		tmp = expander_asterisk(cmd[i]);
		if (tmp)
		{
			free(cmd[i]);
			cmd[i] = tmp;
		}
		i++;
	}
}

void	expander_main(t_data *data, t_node *ast)
{
	if (!ast)
		return ;

	if (ast->command)
	{
		_heredoc(data, ast->command);
		expander_var(ast->command->args, data);
		_asterisk(ast->command->args);
	}
	expander_main(data, ast->left);
	expander_main(data, ast->right);
}
