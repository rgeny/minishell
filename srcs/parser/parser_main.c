/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 21:49:56 by tokino            #+#    #+#             */
/*   Updated: 2022/02/05 19:29:25 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "ast_print.h"

int	parser_main(t_data *data, char *rl)
{
	t_token	*tokens;

	error_reset();
	tokens = lexer_lex(rl);
	lexer_print_tokens(tokens);
	data->ast_root = parse_tokens(tokens);
	print_ast_the_fancy_way(data->ast_root);
	lexer_free_tokens(&tokens);
	return (error_get());
}
