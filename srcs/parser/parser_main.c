/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 21:49:56 by tokino            #+#    #+#             */
/*   Updated: 2022/02/11 14:56:53 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "ast_print.h"

int	print_syntax_error(t_token *token)
{
	if (token)
		return (error_print(TOKEN_ERROR, token->content, "'\n", ERROR_TOKEN));
	return (error_print(TOKEN_ERROR, "newline", "'\n", ERROR_TOKEN));
}

int	parser_main(t_data *data, char *rl)
{
	t_token	*tokens;

	error_reset();
	tokens = lexer_lex(rl);
//	lexer_print_tokens(tokens);
	data->ast = build_ast(tokens, data->env);
//	print_ast(data->ast);
	lexer_free_tokens(&tokens);
	return (error_get());
}
