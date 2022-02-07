/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init_pipeline_list.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 14:00:24 by tokino            #+#    #+#             */
/*   Updated: 2022/02/07 14:40:12 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_node	*_init_pipeline(t_token **tokens)
{
	t_node	*pipeline_node;

	if (!is_error() && is_opened_parenthesis_token(*tokens))
	{
		*tokens = (*tokens)->next;
		pipeline_node = init_pipeline_list(tokens, true);
	}
	else
		pipeline_node = init_pipeline(tokens);
	return (pipeline_node);
}

static bool	_is_valid_token(t_token *token)
{
	t_token_type	type;

	if (!token)
		return (false);
	type = token->type;
	return (is_list_token(token) || type == E_TOKEN_TYPE_PARENTHESIS_OPEN);
}

static t_node	*_init_right_pipeline(t_token **tokens)
{
	t_node	*pipeline_node;

	pipeline_node = NULL;
	if (!is_error() && _is_valid_token((*tokens)->next))
	{
		*tokens = (*tokens)->next;
		if (is_list_token(*tokens))
			pipeline_node = init_pipeline(tokens);
		else if (is_opened_parenthesis_token(*tokens))
		{
			*tokens = (*tokens)->next;
			pipeline_node = init_pipeline_list(tokens, true);
		}
	}
	else
		print_syntax_error(*tokens);
	return (pipeline_node);
}

static t_node	*_set_list_root(t_node *main_node, t_node *separator_node, bool is_subshell)
{
	t_node	*root;

	if (separator_node)
		root = separator_node;
	else
		root = main_node;
	if (root && root->type != E_NODE_TYPE_COMMAND && is_subshell)
		root->is_subshell = true;
	return (root);
}

t_node	*init_pipeline_list(t_token **tokens, bool is_subshell)
{
	t_node		*pipeline_node;
	t_node		*andor_node;

	if (error_get() != SUCCESS)
		return (NULL);
	andor_node = NULL;
	pipeline_node = _init_pipeline(tokens);
	while (!is_error() && _is_valid_token(*tokens))
	{
		andor_node = init_separator_node(*tokens, andor_node, pipeline_node);
		andor_node->right = _init_right_pipeline(tokens);
	}
	if (!is_error() && is_subshell)
	{
		if (is_closed_parenthesis_token(*tokens))
			*tokens = (*tokens)->next;
		else
			print_syntax_error(*tokens);
	}
	return (_set_list_root(pipeline_node, andor_node, is_subshell));
}
