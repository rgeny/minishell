/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_n_create.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 11:36:35 by tokino            #+#    #+#             */
/*   Updated: 2022/01/26 11:54:47 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast_node	*n_create(t_ast_node_type type)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (node == NULL)
		return (NULL); // TODO : Clean all and exit OR raise error
	node->type = type;
	node->left = NULL;
	node->right = NULL;
	if (type == E_AST_NODE_TYPE_COMMAND)
	{
		node->command = malloc(sizeof(t_command));
		if (node->command == NULL)
			return (NULL); // TODO : Clean all and exit OR raise error
		node->command->args = NULL;
		node->command->redirections = NULL;
	}
	else
	{
		node->command = NULL;
	}
	return (node);
}
