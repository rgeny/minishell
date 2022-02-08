/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init_pipeline.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 13:42:43 by tokino            #+#    #+#             */
/*   Updated: 2022/02/08 12:28:31 by tokino           ###   ########.fr       */
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

t_node	*_set_pipeline_root(t_node *main_node, t_node *separator_node)
{
	if (separator_node)
		return (separator_node);
	else
		return (main_node);
}

t_node	*init_pipeline(t_token **tokens)
{
	t_node	*command_node;
	t_node	*pipe_node;

	if (is_error())
		return (NULL);
	pipe_node = NULL;
	command_node = init_command(tokens);
	while (!is_error() && _is_pipe_token(*tokens))
	{
		pipe_node = init_separator_node(tokens, pipe_node, command_node);
		pipe_node->right = init_command(tokens);
	}
	return (_set_pipeline_root(command_node, pipe_node));
}
