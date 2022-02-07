/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_n_create.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 11:36:35 by tokino            #+#    #+#             */
/*   Updated: 2022/02/07 11:19:33 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_node	*n_create(t_node_type type)
{
	t_node	*node;

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
