/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 12:21:43 by tokino            #+#    #+#             */
/*   Updated: 2022/02/06 10:40:52 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	is_command_token(t_token_type type)
{
	return (type == E_TOKEN_TYPE_WORD || type == E_TOKEN_TYPE_REDIRECTION);
}

static t_node	*_set_root(t_node *n_command, t_node *n_separator)
{
	if (n_separator)
		return (n_separator);
	else
		return (n_command);
}

t_node	*parse_tokens(t_token *tokens)
{
	t_token	*current_token;
	t_node	*n_command;
	t_node	*n_separator;

	if (tokens == NULL || error_get() != SUCCESS)
		return (NULL);
	current_token = tokens;
	n_separator = NULL;
	n_command = NULL;

	init_n_command(&current_token, &n_command, n_separator);
	while (current_token && error_get() == SUCCESS)
	{
		init_n_pipe(&n_separator, n_command);
		if (current_token->next)
		{
			current_token = current_token->next;
			init_n_command(&current_token, &n_command, n_separator);
		}
		else
			print_syntax_error(current_token); // tokens finished by a pipe
	}
	
	return (_set_root(n_command, n_separator));
}
