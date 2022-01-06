/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token_constructor.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 18:18:30 by tokino            #+#    #+#             */
/*   Updated: 2022/01/06 11:02:41 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static t_token *lexer_token_create(char *content)
{
	t_token *token;

	token = (t_token *)malloc(sizeof(t_token));
	token->content = content;
	token->next = NULL;
	return (token);
}

void    lexer_tok_constructor_new(t_tok_constructor *constructor, int start_index)
{
	t_token *token;

	token = lexer_token_create(NULL);
	constructor->current_token = token;
	constructor->mode = E_MODE_WORD;
	constructor->start_index = start_index;
}

void    lexer_tok_constructor_init(t_tok_constructor *constructor, const char *str)
{
	constructor->mode = E_MODE_WORD;
	constructor->start_index = 0;
	constructor->current_token = NULL;
	constructor->str = str;
}

void	lexer_tok_constructor_free(t_tok_constructor *constructor)
{
	if (constructor->current_token)
		lexer_free_tokens(&constructor->current_token);
	else
		printf("No tok constructor to free\n");
}