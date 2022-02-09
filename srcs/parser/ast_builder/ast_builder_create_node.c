/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder_create_node.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 11:36:35 by tokino            #+#    #+#             */
/*   Updated: 2022/02/09 15:56:32 by tokino           ###   ########.fr       */
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
	node->is_subshell = false;
	if (type == E_NODE_TYPE_COMMAND)
	{
		node->cmd = uti_calloc(1, sizeof(t_command));
		if (node->cmd == NULL)
			return (NULL);
		node->cmd->cargs = NULL;
		node->cmd->redirections = NULL;
	}
	else
	{
		node->cmd = NULL;
	}
	return (node);
}
