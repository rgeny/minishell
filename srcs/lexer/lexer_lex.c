/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_lex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 10:49:30 by tokino            #+#    #+#             */
/*   Updated: 2022/02/02 14:29:40 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	_terminate_token_and_create_a_new_one(
				t_tok_constructor *c, t_token **tokens, int i)
{
	lexer_terminate_token(c, tokens, i);
	lexer_tok_constructor_new(c, i + 1);
	if (c->cur_token == NULL)
		return (MALLOC_ERROR_CODE);
	return (OK);
}

static int	_process_char(t_tok_constructor *c, t_token **tokens, int i)
{
	int	len;

	if (c->mode == E_MODE_WORD)
	{
		if (lexer_get_chartype(c->str[i]) == E_CHAR_TYPE_BLANK)
		{
			if (_terminate_token_and_create_a_new_one(c, tokens, i))
				return (MALLOC_ERROR_CODE);
			return (1);
		}
		else if (lexer_get_chartype(c->str[i]) == E_CHAR_TYPE_OPERATOR)
		{
			if (_terminate_token_and_create_a_new_one(c, tokens, i))
				return (MALLOC_ERROR_CODE);
			len = lexer_create_operator_tok(c, tokens, i);
			lexer_tok_constructor_new(c, i + len);
			if (c->cur_token == NULL)
				return (MALLOC_ERROR_CODE);
			return (len);
		}
		else
			return (lexer_update_token_mode(c, c->str[i]));
	}
	else
		return (lexer_update_token_mode(c, c->str[i]));
}

void *_print_lexer_error(t_data *data, int error_code, t_token **tokens)
{
	char *msg;

	if (error_code == QUOTE_ERROR_CODE)
	{
		msg = "Syntax error: Please close all your quotes\n";
		print_error(msg, NULL, NULL, data);
	}
	else if (error_code == MALLOC_ERROR_CODE)
	{
		print_error("Error: Cannot allocate memory\n", NULL, NULL, data);
	}
	lexer_free_tokens(tokens);
	return (NULL);
} 

t_token	*lexer_lex(t_data *data, const char *str)
{
	int					i;
	int					len;
	t_tok_constructor	constructor;
	t_token				*tokens;

	lexer_tok_constructor_init(&constructor, str);
	tokens = NULL;
	i = 0;
	lexer_tok_constructor_new(&constructor, i);
	if (constructor.cur_token == NULL)
		return (_print_lexer_error(data, MALLOC_ERROR_CODE, &tokens));
	while (str && str[i])
	{
		len = _process_char(&constructor, &tokens, i);
		if (len == MALLOC_ERROR_CODE)
			return (_print_lexer_error(data, MALLOC_ERROR_CODE, &tokens));
		i += len;
	}
	if (constructor.cur_token)
	{
		if (constructor.mode != E_MODE_WORD)
			return (_print_lexer_error(data, QUOTE_ERROR_CODE, &tokens));
		lexer_terminate_token(&constructor, &tokens, i);
	}
	lexer_tok_constructor_free(&constructor);
	return (tokens);
}
