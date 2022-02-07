/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init_pipeline.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 13:42:43 by tokino            #+#    #+#             */
/*   Updated: 2022/02/07 11:20:31 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static bool	_is_pipeline_token(t_token_type type)
{
	return (is_command_token(type) || type == E_TOKEN_TYPE_PIPE);
}

static t_node	*_init_pipe_node(t_node *pipe_node, t_node *command_node)
{
	t_node	*new_pipe_node;

	new_pipe_node = n_create(E_NODE_TYPE_PIPE);
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

static bool	_is_valid_token(t_token_type type)
{
	return (_is_pipeline_token(type) || type == E_TOKEN_TYPE_PARENTHESIS_OPEN);
}

t_node	*init_pipeline(t_token **tokens)
{
	t_node	*command_node;
	t_node	*pipe_node;

	if (error_get() != SUCCESS)
		return (NULL);
	if (!_is_pipeline_token((*tokens)->type))
	{
		print_syntax_error(*tokens);
		return (NULL);
	}
	pipe_node = NULL;
	command_node = init_command(tokens);
	if (*tokens && (*tokens)->type == E_TOKEN_TYPE_PARENTHESIS_OPEN)
		print_syntax_error(*tokens); 
	while (*tokens && _is_valid_token((*tokens)->type) && error_get() == SUCCESS)
	{
		pipe_node = _init_pipe_node(pipe_node, command_node);
		if ((*tokens)->next && error_get() == SUCCESS && _is_valid_token((*tokens)->next->type))
		{
			*tokens = (*tokens)->next;
			if (_is_pipeline_token((*tokens)->type))
				pipe_node->right = init_command(tokens);
			else if ((*tokens)->type == E_TOKEN_TYPE_PARENTHESIS_OPEN)
			{
				// printf("( spotted !!\n");
				increase_subshell_lvl();
				*tokens = (*tokens)->next;
				pipe_node->right = init_pipeline_list(tokens, true);
			}
		}
		else // if ((*token)->next == NULL)
			print_syntax_error(*tokens); // tokens finished by a pipe

	}
	return (_set_pipeline_root(command_node, pipe_node));
}
