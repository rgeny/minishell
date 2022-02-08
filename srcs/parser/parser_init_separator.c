/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init_separator.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 14:36:52 by tokino            #+#    #+#             */
/*   Updated: 2022/02/08 14:49:40 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_node	*init_separator_node(t_ast_constructor *astc, t_node *sep_node, t_node *cmd_node)
{
	t_node		*new_separator_node;
	t_node_type	type;

	if (is_error())
		return (NULL);
	if (astc->tokens->type == E_TOKEN_TYPE_PIPE)
		type = E_NODE_TYPE_PIPE;
	else if (astc->tokens->type == E_TOKEN_TYPE_OR)
		type = E_NODE_TYPE_OR;
	else
		type = E_NODE_TYPE_AND;
	new_separator_node = create_node(type);
	if (new_separator_node == NULL)
		return (NULL);
	if (!sep_node)
		new_separator_node->left = cmd_node;
	else
		new_separator_node->left = sep_node;
	astc->tokens = astc->tokens->next;
	return (new_separator_node);
}
