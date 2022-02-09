/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder_pipeline_list.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 14:00:24 by tokino            #+#    #+#             */
/*   Updated: 2022/02/09 14:55:12 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static bool	_is_andor_token(t_token *token)
{
	t_token_type	type;

	if (!token)
		return (false);
	type = token->type;
	return (type == E_TOKEN_TYPE_OR || type == E_TOKEN_TYPE_AND);
}

static t_ast	*_build_andor_node(t_ast_constructor *astc, \
					t_ast *andor_node, t_ast *pipeline_node)
{
	t_ast		*new_andor_node;
	t_node_type	type;

	if (astc->tokens->type == E_TOKEN_TYPE_OR)
	{
		eat_token(astc, E_TOKEN_TYPE_OR);
		type = E_NODE_TYPE_OR;
	}
	else
	{
		eat_token(astc, E_TOKEN_TYPE_AND);
		type = E_NODE_TYPE_AND;
	}
	new_andor_node = create_node(type);
	if (new_andor_node == NULL)
		return (NULL);
	if (!andor_node)
		new_andor_node->left = pipeline_node;
	else
		new_andor_node->left = andor_node;
	return (new_andor_node);
}

static t_ast	*_set_list_root(
					t_ast *main_node, t_ast *separator_node, bool is_subshell)
{
	t_ast	*root;

	if (separator_node)
		root = separator_node;
	else
		root = main_node;
	if (root && root->type != E_NODE_TYPE_COMMAND && is_subshell)
		root->is_subshell = true;
	return (root);
}

t_ast	*build_pipeline_list(t_ast_constructor *astc, bool is_subshell)
{
	t_ast		*pipeline_node;
	t_ast		*andor_node;

	if (is_error())
		return (NULL);
	andor_node = NULL;
	pipeline_node = build_pipeline(astc);
	while (!is_error() && _is_andor_token(astc->tokens))
	{
		andor_node = _build_andor_node(astc, andor_node, pipeline_node);
		andor_node->right = build_pipeline(astc);
	}
	return (_set_list_root(pipeline_node, andor_node, is_subshell));
}
