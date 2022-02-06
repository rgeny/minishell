/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 12:21:43 by tokino            #+#    #+#             */
/*   Updated: 2022/02/06 14:55:41 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	is_command_token(t_token_type type)
{
	return (type == E_TOKEN_TYPE_WORD || type == E_TOKEN_TYPE_REDIRECTION);
}

t_node	*parse_tokens(t_token *tokens)
{
	t_token	*current_token;
	t_node	*root;

	if (tokens == NULL || error_get() != SUCCESS)
		return (NULL);
	current_token = tokens;
	root = init_pipeline_list(&current_token, 0);
	if (current_token && current_token->type == E_TOKEN_TYPE_OPERATOR)
		print_syntax_error(current_token);
	return (root);
}
