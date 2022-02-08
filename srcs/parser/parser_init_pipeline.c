/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init_pipeline.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 13:42:43 by tokino            #+#    #+#             */
/*   Updated: 2022/02/08 15:17:07 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static bool	_is_pipe_token(t_token *token)
{
	t_token_type	type;

	if (!token)
		return (false);
	type = token->type;
	return (type == E_TOKEN_TYPE_PIPE);
}

static t_node	*_init_pipe_node(t_ast_constructor *astc, t_node *pipe_node, t_node *command_node)
{
	t_node	*new_pipe_node;

	eat_token(astc, E_TOKEN_TYPE_PIPE);
	new_pipe_node = create_node(E_NODE_TYPE_PIPE);
	if (new_pipe_node == NULL)
		return (NULL);
	if (!pipe_node)
		new_pipe_node->left = command_node;
	else
		new_pipe_node->left = pipe_node;
	return (new_pipe_node);
}

t_node	*_set_pipeline_root(t_node *main_node, t_node *separator_node)
{
	if (separator_node)
		return (separator_node);
	else
		return (main_node);
}

t_node	*init_pipeline(t_ast_constructor *astc)
{
	t_node	*command_node;
	t_node	*pipe_node;

	if (is_error())
		return (NULL);
	pipe_node = NULL;
	command_node = init_command(astc);
	while (!is_error() && _is_pipe_token(astc->tokens))
	{
		pipe_node = _init_pipe_node(astc, pipe_node, command_node);
		pipe_node->right = init_command(astc);
	}
	return (_set_pipeline_root(command_node, pipe_node));
}
