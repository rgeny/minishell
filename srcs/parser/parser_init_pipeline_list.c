/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init_pipeline_list.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 14:00:24 by tokino            #+#    #+#             */
/*   Updated: 2022/02/08 14:47:36 by tokino           ###   ########.fr       */
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

static t_node	*_set_list_root(
					t_node *main_node, t_node *separator_node, bool is_subshell)
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

t_node	*init_pipeline_list(t_ast_constructor *astc, bool is_subshell)
{
	t_node		*pipeline_node;
	t_node		*andor_node;

	if (is_error())
		return (NULL);
	andor_node = NULL;
	pipeline_node = init_pipeline(astc);
	while (!is_error() && _is_andor_token(astc->tokens))
	{
		andor_node = init_separator_node(astc, andor_node, pipeline_node);
		andor_node->right = init_pipeline(astc);
	}
	return (_set_list_root(pipeline_node, andor_node, is_subshell));
}
