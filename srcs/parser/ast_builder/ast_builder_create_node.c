/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder_create_node.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 11:36:35 by tokino            #+#    #+#             */
/*   Updated: 2022/02/10 09:49:42 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast	*create_node(t_node_type type)
{
	t_ast	*node;

	if (is_error())
		return (NULL);
	node = uti_calloc(1, sizeof(t_ast));
	if (node == NULL)
		return (NULL);
	node->type = type;
	node->left = NULL;
	node->right = NULL;
	node->pid = 0;
	node->is_subshell = false;
	if (type == E_NODE_TYPE_COMMAND)
	{
		node->cmd = uti_calloc(1, sizeof(t_command));
		if (node->cmd == NULL)
			return (NULL);
		node->cmd->cargs = NULL;
		node->cmd->redirections = NULL;
		node->cmd->fd_heredoc = STDIN_FILENO;
		node->cmd->pid = 0;
	}
	else
		node->cmd = NULL;
	return (node);
}
