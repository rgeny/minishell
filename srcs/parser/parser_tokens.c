/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 12:21:43 by tokino            #+#    #+#             */
/*   Updated: 2022/02/06 13:34:17 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	is_command_token(t_token_type type)
{
	return (type == E_TOKEN_TYPE_WORD || type == E_TOKEN_TYPE_REDIRECTION);
}

bool	is_pipeline_token(t_token_type type)
{
	return (is_command_token(type) || type == E_TOKEN_TYPE_PIPE);
}

static t_node	*_set_root(t_node *main_node, t_node *separator_node)
{
	if (separator_node)
		return (separator_node);
	else
		return (main_node);
}

t_node	*init_pipeline(t_token **token)
{
	t_node	*command_node;
	t_node	*pipe_node;

	if (error_get() != SUCCESS)
		return (NULL);
	pipe_node = NULL;
	command_node = NULL;
	init_n_command(token, &command_node, pipe_node);
	while (*token && is_pipeline_token((*token)->type) && error_get() == SUCCESS)
	{
		init_n_pipe(&pipe_node, command_node);
		if ((*token)->next)
		{
			*token = (*token)->next;
			init_n_command(token, &command_node, pipe_node);
		}
		else
			print_syntax_error(*token); // tokens finished by a pipe
	}
	return (_set_root(command_node, pipe_node));
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
		andor_node = init_andor_node(andor_node, pipeline_node, (*tokens)->type);
		if ((*tokens)->next)
		{
			*tokens = (*tokens)->next;
			new_pipeline_node = init_pipeline(tokens);
			andor_node->right = new_pipeline_node;
		}
		else
			print_syntax_error(*tokens); // tokens finished by a pipe
	}
	return (_set_root(pipeline_node, andor_node));
}

t_node	*parse_tokens(t_token *tokens)
{
	t_token	*current_token;
	t_node	*root;

	if (tokens == NULL || error_get() != SUCCESS)
		return (NULL);
	current_token = tokens;
	root = init_pipeline_list(&current_token);
	return (root);
}
