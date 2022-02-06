/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init_pipeline.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 13:42:43 by tokino            #+#    #+#             */
/*   Updated: 2022/02/06 13:57:13 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static bool	_is_pipeline_token(t_token_type type)
{
	return (is_command_token(type) || type == E_TOKEN_TYPE_PIPE);
}

static void	_init_n_pipe(t_node **pipe_node, t_node *n_command)
{
	t_node	*new_n_separator;

	new_n_separator = n_create(E_NODE_TYPE_PIPE);
	if (new_n_separator == NULL)
		return ;
	if (!*pipe_node)
		new_n_separator->left = n_command;
	else
		new_n_separator->left = *pipe_node;
	*pipe_node = new_n_separator;
}

t_node	*_set_pipeline_root(t_node *main_node, t_node *separator_node)
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
	while (*token && _is_pipeline_token((*token)->type) && error_get() == SUCCESS)
	{
		_init_n_pipe(&pipe_node, command_node);
		if ((*token)->next)
		{
			*token = (*token)->next;
			init_n_command(token, &command_node, pipe_node);
		}
		else
			print_syntax_error(*token); // tokens finished by a pipe
	}
	return (_set_pipeline_root(command_node, pipe_node));
}
