/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_lex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 10:49:30 by tokino            #+#    #+#             */
/*   Updated: 2022/01/06 11:28:48 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	_process_char(t_tok_constructor *constructor, t_token **tokens, int i)
{
	int	len;

	if (constructor->mode == E_MODE_WORD)
	{
		if (lexer_get_chartype(constructor->str[i]) == E_CHAR_TYPE_BLANK)
		{
			lexer_terminate_token(constructor, tokens, i);
			lexer_tok_constructor_new(constructor, i + 1);
			return (1);
		}
		else if (lexer_get_chartype(constructor->str[i]) == E_CHAR_TYPE_OPERATOR)
		{
			lexer_terminate_token(constructor, tokens, i);
			lexer_tok_constructor_new(constructor, i + 1);
			len = lexer_create_operator_token(constructor, tokens, i);
			lexer_tok_constructor_new(constructor, i + len);
			return (len);
		}
		else
			return (lexer_update_token_mode(constructor, constructor->str[i]));
	}
	else
		return (lexer_update_token_mode(constructor, constructor->str[i]));
}

t_token	*lexer_lex(const char *str)
{
	int					i;
	t_tok_constructor	constructor;
	t_token				*tokens;

	lexer_tok_constructor_init(&constructor, str);
	tokens = NULL;
	i = 0;
	lexer_tok_constructor_new(&constructor, i);
	while (str && str[i])
		i += _process_char(&constructor, &tokens, i);
	if (constructor.cur_token)
		lexer_terminate_token(&constructor, &tokens, i);
	lexer_tok_constructor_free(&constructor);
	return (tokens);
}
