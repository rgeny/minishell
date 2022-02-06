/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_n_separator.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 11:49:27 by tokino            #+#    #+#             */
/*   Updated: 2022/02/06 13:43:14 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"


t_node	*init_andor_node(t_node *andor_node, t_node *pipeline_node, t_token_type token_type)
{
	t_node	*new_andor_node;
	t_node_type	type;
	
	if (token_type == E_TOKEN_TYPE_OR)
		type = E_NODE_TYPE_OR;
	else //if (token_type == E_TOKEN_TYPE_AND)
		type = E_NODE_TYPE_AND;
	new_andor_node = n_create(type);
	if (new_andor_node == NULL)
		return (NULL) ;
	if (!andor_node)
		new_andor_node->left = pipeline_node;
	else
		new_andor_node->left = andor_node;
	return (new_andor_node);
}
