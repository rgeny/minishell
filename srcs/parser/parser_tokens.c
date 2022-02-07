/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 12:21:43 by tokino            #+#    #+#             */
/*   Updated: 2022/02/07 13:11:02 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_node	*parse_tokens(t_token *tokens)
{
	t_token	*current_token;
	t_node	*root;

	if (tokens == NULL || error_get() != SUCCESS)
		return (NULL);
	current_token = tokens;
	root = init_pipeline_list(&current_token, false);
	if (!is_error() && current_token && (current_token->type == E_TOKEN_TYPE_OPERATOR || current_token->type == E_TOKEN_TYPE_PARENTHESIS_CLOSE))
		print_syntax_error(current_token);
	return (root);
}
