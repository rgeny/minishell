/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 21:49:56 by tokino            #+#    #+#             */
/*   Updated: 2022/02/13 14:53:46 by tokino           ###   ########.fr       */
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
	if (data->is_verbose_mod)
		lexer_print_tokens(tokens);
	data->ast = build_ast(tokens, data->env);
	if (data->is_verbose_mod)
		print_ast(data->ast);
	lexer_free_tokens(&tokens);
	str_free(&rl);
	return (error_get());
}
