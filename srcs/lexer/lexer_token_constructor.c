/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token_constructor.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 18:18:30 by tokino            #+#    #+#             */
/*   Updated: 2022/01/25 13:01:02 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static t_token	*_lexer_token_create()
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	token->content = NULL;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

void	lexer_tok_constructor_new(t_tok_constructor *constructor, int stri)
{
	t_token	*token;

	token = _lexer_token_create();
	constructor->cur_token = token;
	constructor->mode = E_MODE_WORD;
	constructor->start_index = stri;
}

void	lexer_tok_constructor_init(t_tok_constructor *constructor, const char *str)
{
	constructor->mode = E_MODE_WORD;
	constructor->start_index = 0;
	constructor->cur_token = NULL;
	constructor->str = str;
}

void	lexer_tok_constructor_free(t_tok_constructor *constructor)
{
	if (constructor->cur_token)
		lexer_free_tokens(&constructor->cur_token);
}
