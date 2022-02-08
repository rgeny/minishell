/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_n_create.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 11:36:35 by tokino            #+#    #+#             */
/*   Updated: 2022/02/08 15:16:42 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_node	*create_node(t_node_type type)
{
	t_node	*node;
	
	if (is_error())
		return (NULL);
	node = uti_calloc(1, sizeof(t_node));
	if (node == NULL)
		return (NULL);
	node->type = type;
	node->left = NULL;
	node->right = NULL;
	node->is_subshell = false;
	if (type == E_NODE_TYPE_COMMAND)
	{
		node->command = uti_calloc(1, sizeof(t_command));
		if (node->command == NULL)
			return (NULL);
		node->command->args = NULL;
		node->command->redirections = NULL;
	}
	else
	{
		node->command = NULL;
	}
	return (node);
}
