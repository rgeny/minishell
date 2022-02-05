/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_lex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 10:49:30 by tokino            #+#    #+#             */
/*   Updated: 2022/02/05 17:06:01 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	_terminate_token_and_create_a_new_one(
				t_tok_constructor *c, t_token **tokens, int i)
{
	lexer_terminate_token(c, tokens, i);
	lexer_tok_constructor_new(c, i + 1);
}

static int	_process_char(t_tok_constructor *c, t_token **tokens, int i)
{
	int	len;

	if (error_get()!= SUCCESS)
		return 0;
	if (c->mode == E_MODE_WORD)
	{
		if (lexer_get_chartype(c->str[i]) == E_CHAR_TYPE_BLANK)
		{
			_terminate_token_and_create_a_new_one(c, tokens, i);
			return (1);
		}
		else if (lexer_get_chartype(c->str[i]) == E_CHAR_TYPE_OPERATOR)
		{
			_terminate_token_and_create_a_new_one(c, tokens, i);
			len = lexer_create_operator_tok(c, tokens, i);
			lexer_tok_constructor_new(c, i + len);
			return (len);
		}
		else
			return (lexer_update_token_mode(c, c->str[i]));
	}
	else
		return (lexer_update_token_mode(c, c->str[i]));
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
	while (str && str[i] && error_get() == SUCCESS)
		i += _process_char(&constructor, &tokens, i);;
	if (constructor.cur_token && error_get() == SUCCESS)
	{
		if (constructor.mode != E_MODE_WORD)
			error_print(QUOTE_ERROR, NULL, NULL, ERROR_SYNTAX);
		lexer_terminate_token(&constructor, &tokens, i);
	}
	lexer_tok_constructor_free(&constructor);
	return (tokens);
}
