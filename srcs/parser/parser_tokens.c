/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 12:21:43 by tokino            #+#    #+#             */
/*   Updated: 2022/02/08 17:09:39 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_ast_constructor	*_init_astc(t_token *tokens)
{
	t_ast_constructor	*astc;

	astc = uti_calloc(1, sizeof(astc));
	astc->tokens = tokens;
	return (astc);
}

void	eat_token(t_ast_constructor *astc, t_token_type type)
{
	if (astc->tokens && astc->tokens->type == type)
		astc->tokens = astc->tokens->next;
	else if (!is_error())
		print_syntax_error(astc->tokens);
}

t_node	*parse_tokens(t_token *tokens)
{
	t_node				*root;
	t_ast_constructor	*astc;

	if (tokens == NULL || is_error())
		return (NULL);
	astc = _init_astc(tokens);
	root = init_pipeline_list(astc, false);
	if (!is_error() && astc->tokens)
		print_syntax_error(astc->tokens);
	return (root);
}
