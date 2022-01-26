/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_n_create.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 11:36:35 by tokino            #+#    #+#             */
/*   Updated: 2022/01/26 17:44:41 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_node	*n_create(t_node_type type)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (node == NULL)
		return (NULL);
	node->type = type;
	node->left = NULL;
	node->right = NULL;
	if (type == E_NODE_TYPE_COMMAND)
	{
		node->command = malloc(sizeof(t_command));
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
