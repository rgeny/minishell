/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 12:21:43 by tokino            #+#    #+#             */
/*   Updated: 2022/01/26 11:55:03 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	is_command_token(t_token_type type)
{
	return (type == E_TOKEN_TYPE_WORD || type == E_TOKEN_TYPE_REDIRECTION);
}

int	parse_tokens(t_data *data, t_token *tokens)
{
	t_token		*current_token;
	t_ast_node	*n_command;
	t_ast_node	*n_separator;

	current_token = tokens;
	n_separator = NULL;
	if (create_and_set_n_command(&current_token, &n_command, n_separator))
		return (print_syntax_error(current_token)); // Error in command syntax or line start by a separator
	while (current_token)
	{
		create_and_set_n_separator(&n_separator, n_command);
		if (!current_token->next) // Line terminate by a separator (|, ||, &&)
			return (print_syntax_error(current_token));
		current_token = current_token->next;
		if (create_and_set_n_command(&current_token, &n_command, n_separator))
			return (print_syntax_error(current_token)); // Error in command syntax or 2 consecutives separators
	}
	if (n_separator)
		data->ast_root = n_separator;
	else
		data->ast_root = n_command;
	print_ast(data->ast_root, 0);
	return (0);
}
