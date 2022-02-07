/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init_pipeline_list.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 14:00:24 by tokino            #+#    #+#             */
/*   Updated: 2022/02/07 11:02:57 by tokino           ###   ########.fr       */
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

static bool	_is_valid_token(t_token_type type)
{
	return (_is_list_token(type) || type == E_TOKEN_TYPE_PARENTHESIS_OPEN);
}

t_node	*init_pipeline_list(t_token **tokens)
{
	t_node	*pipeline_node;
	t_node	*andor_node;
	t_node_type	type;
	
	if (error_get() != SUCCESS)
		return (NULL);
	andor_node = NULL;

	if (*tokens && error_get() == SUCCESS && (*tokens)->type == E_TOKEN_TYPE_PARENTHESIS_OPEN)
	{
		printf("( spotted !!\n");
		*tokens = (*tokens)->next;
		pipeline_node = init_pipeline_list(tokens);
	}
	else
	{
		pipeline_node = init_pipeline(tokens);
	}
	while (*tokens && _is_valid_token((*tokens)->type) && error_get() == SUCCESS)
	{
		type = _get_node_type(*tokens);
		andor_node = _init_andor_node(andor_node, pipeline_node, type);

		if ((*tokens)->next && error_get() == SUCCESS && _is_valid_token((*tokens)->next->type))
		{
			*tokens = (*tokens)->next;
			if (_is_list_token((*tokens)->type))
				andor_node->right = init_pipeline(tokens);
			else if ((*tokens)->type == E_TOKEN_TYPE_PARENTHESIS_OPEN)
			{
				printf("( spotted !!\n");
				*tokens = (*tokens)->next;
				andor_node->right = init_pipeline_list(tokens);
			}
		}
		else
			print_syntax_error(*tokens); // list finished by && or ||
	}

	// Here I can have a closed )
	if (*tokens && error_get() == SUCCESS && (*tokens)->type == E_TOKEN_TYPE_PARENTHESIS_CLOSE)
	{
		printf(") spotted !!\n");
		*tokens = (*tokens)->next;
	}

	return (_set_list_root(pipeline_node, andor_node));
}
