/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 16:54:37 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/01 14:24:12 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "expander.h"
#include "str.h"

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

static void	_asterisk_cmd(t_carg *cmd)
{
	char	*tmp;

	while (cmd)
	{
		tmp = expander_asterisk(cmd->content);
		if (tmp)
		{
			free(cmd->content);
			cmd->content = tmp;
		}
		cmd = cmd->next;
	}
}

static void	_join_and_split_cmd(t_command *cmd)
{
	t_carg	*tmp;
	int		len;
	char	**ret;
	int		i;

	tmp = cmd->cargs;
	len = 0;
	while (tmp)
	{
		tmp = tmp->next;
		len++;
	}
	str_free_list(cmd->args);
	ret = malloc(sizeof(char *) * (len + 1));
	ret[len] = 0;
	tmp = cmd->cargs;
	i = 0;
	while (i < len)
	{
		ret[i] = str_dup(tmp->content);
		i++;
		tmp = tmp->next;
	}
	cmd->args = ret;
/*	int		i;
	char	*join;
	char	*tmp;
	char	**split;

	join = NULL;
	i = 0;
	while (cmd[0][i])
	{
		tmp = str_join(join, cmd[0][i], ' ');
		str_free(join);
		join = tmp;
		i++;
	}
	split = str_split(join, " ");
	str_free_list(cmd[0]);
	cmd[0] = split;*/
}

void	expander_main(t_data *data, t_node *ast)
{
	if (!ast)
		return ;

	if (ast->command)
	{
		_heredoc(data, ast->command);
		expander_var(ast->command->cargs, data);
		_asterisk_cmd(ast->command->cargs);
		_join_and_split_cmd(ast->command);
	}
	expander_main(data, ast->left);
	expander_main(data, ast->right);
}
