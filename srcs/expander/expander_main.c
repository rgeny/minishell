/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 16:54:37 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/08 10:49:25 by buschiix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "expander.h"
#include "str.h"

static void	_heredoc(t_command *cmd)
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
			fd = expander_heredoc(cmd->redirections[i].path);
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

	if (!str_cmp(cmd->content, "echo")) //a delete
		cmd = cmd->next;
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
	int		j;
	int		k;
	int		b;
	char	*t1;
	char	*t2;

	tmp = cmd->cargs;
	len = 0;
	while (tmp) //count arg
	{
		i = 0;
		b = 0;
		while (tmp->content[i])
		{
			if (!b && (tmp->content[i] == '\'' || tmp->content[i] == '\"'))
				b = tmp->content[i];
			else if (b && tmp->content[i] == b)
				b = 0;
			else if (!b && tmp->content[i] == ' ')
			{
				while (tmp->content[i + 1] == ' ')
					i++;
				if (tmp->content[i + 1])
					len++;
			}
			i++;
		}
		if (tmp->content[0] || tmp->next)
			len++;
		tmp = tmp->next;
	}
	str_free_list(cmd->args);
	ret = malloc(sizeof(char *) * (len + 1));
	ret[len] = NULL;
	tmp = cmd->cargs;
	i = 0;
	while (tmp && i < len) //split
	{
		j = 0;
		k = 0;
		b = 0;
		while (tmp->content[j] && i < len)
		{
			if (!b && (tmp->content[j] == '\'' || tmp->content[j] == '\"'))
				b = tmp->content[j];
			else if (b && tmp->content[j] == b)
				b = 0;
			else if (!b && tmp->content[j] == ' ')
			{
				ret[i] = str_ndup(&tmp->content[k], j - k);
				i++;
				while (tmp->content[j + 1] == ' ')
					j++;
				k = j + 1;
			}
			j++;
		}
		ret[i] = str_ndup(&tmp->content[k], j - k);
		i++;
		tmp = tmp->next;
	}
	cmd->args = ret;

	i = 0;
	while (i < len) //delete quote
	{
		j = 0;
		b = 0;
		while (cmd->args[i][j])
		{
			if (!b && (cmd->args[i][j] == '\'' || cmd->args[i][j] == '\"'))
			{
				b = cmd->args[i][j];
				t1 = str_ndup(cmd->args[i], j);
				t2 = str_join(t1, &cmd->args[i][j + 1], 0);
				str_free(t1);
				str_free(cmd->args[i]);
				cmd->args[i] = t2;
			}
			else if (b && cmd->args[i][j] == b)
			{
				b = 0;
				t1 = str_ndup(cmd->args[i], j);
				t2 = str_join(t1, &cmd->args[i][j + 1], 0);
				str_free(t1);
				str_free(cmd->args[i]);
				cmd->args[i] = t2;
			}
			else
				j++;
		}
		i++;
	}
	ret[len] = NULL;
}
#include <stdio.h>
void	_print_test(t_carg *cmd)
{
	while (cmd)
	{
		printf("%s\n", cmd->content);
		cmd = cmd->next;
	}
	printf("\n");
}

void	expander_main(t_data *data, t_node *ast)
{
	if (!ast)
		return ;

	if (ast->command)
	{
		_heredoc(ast->command);
		if (ast->command->cargs)
		{
			expander_var(ast->command->cargs, data);
			_print_test(ast->command->cargs);
			_expand_asterisk(ast->command);
			_print_test(ast->command->cargs);
			_asterisk_cmd(ast->command->cargs);
			_print_test(ast->command->cargs);
		}
		_join_and_split_cmd(ast->command);
	}
	expander_main(data, ast->left);
	expander_main(data, ast->right);
}
