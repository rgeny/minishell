/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_n_separator.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 11:49:27 by tokino            #+#    #+#             */
/*   Updated: 2022/02/06 13:35:54 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	init_n_pipe(t_node **pipe_node, t_node *n_command)
{
	t_node	*new_n_separator;

	new_n_separator = n_create(E_NODE_TYPE_PIPE);
	if (new_n_separator == NULL)
		return ;
	if (!*pipe_node)
		new_n_separator->left = n_command;
	else
		new_n_separator->left = *pipe_node;
	*pipe_node = new_n_separator;
}

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
