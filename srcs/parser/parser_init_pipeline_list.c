/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init_pipeline_list.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 14:00:24 by tokino            #+#    #+#             */
/*   Updated: 2022/02/06 14:06:52 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_node	*_init_andor_node(t_node *andor_node, t_node *pipeline_node, t_token_type token_type)
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

static t_node	*_set_list_root(t_node *main_node, t_node *separator_node)
{
	if (separator_node)
		return (separator_node);
	else
		return (main_node);
}

t_node	*init_pipeline_list(t_token **tokens)
{
	t_node	*new_pipeline_node;
	t_node	*pipeline_node;
	t_node	*andor_node;
	
	if (error_get() != SUCCESS)
		return (NULL);
	
	pipeline_node = init_pipeline(tokens);
	andor_node = NULL;
	while (*tokens && error_get() == SUCCESS)
	{
		andor_node = _init_andor_node(andor_node, pipeline_node, (*tokens)->type);
		if ((*tokens)->next)
		{
			*tokens = (*tokens)->next;
			new_pipeline_node = init_pipeline(tokens);
			andor_node->right = new_pipeline_node;
		}
		else
			print_syntax_error(*tokens); // list finished by && or ||
	}
	return (_set_list_root(pipeline_node, andor_node));
}
