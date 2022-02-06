/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init_pipeline_list.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 14:00:24 by tokino            #+#    #+#             */
/*   Updated: 2022/02/06 15:13:48 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_node	*_init_andor_node(t_node *andor_node, t_node *pipeline_node, t_node_type type)
{
	t_node	*new_andor_node;

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

static t_node_type	_get_node_type(t_token *token)
{
	if (token->type == E_TOKEN_TYPE_OR)
		return (E_NODE_TYPE_OR);
	else //if (token->type == E_TOKEN_TYPE_AND)
		return (E_NODE_TYPE_AND);
}

static bool	_is_list_token(t_token_type type)
{
	return (is_command_token(type)\
			|| type == E_TOKEN_TYPE_PIPE\
			|| type == E_TOKEN_TYPE_AND\
			|| type == E_TOKEN_TYPE_OR);
}

t_node	*init_pipeline_list(t_token **tokens, int subshell_lvl)
{
	t_node	*new_pipeline_node;
	t_node	*pipeline_node;
	t_node	*andor_node;
	t_node_type	type;
	
	if (error_get() != SUCCESS)
		return (NULL);
	
	pipeline_node = init_pipeline(tokens, subshell_lvl);
	andor_node = NULL;
	while (*tokens && _is_list_token((*tokens)->type) && error_get() == SUCCESS)
	{
		type = _get_node_type(*tokens);
		andor_node = _init_andor_node(andor_node, pipeline_node, type);
		if ((*tokens)->next)
		{
			*tokens = (*tokens)->next;
			new_pipeline_node = init_pipeline(tokens, subshell_lvl);
			andor_node->right = new_pipeline_node;
		}
		else
			print_syntax_error(*tokens); // list finished by && or ||
	}
	return (_set_list_root(pipeline_node, andor_node));
}
