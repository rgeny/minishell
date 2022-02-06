/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token_constructor.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 18:18:30 by tokino            #+#    #+#             */
/*   Updated: 2022/02/05 17:07:39 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static t_token	*_lexer_token_create(void)
{
	t_token	*token;

	if (error_get() != SUCCESS)
		return (NULL);
	token = (t_token *)uti_calloc(1, sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->content = NULL;
	token->next = NULL;
	return (token);
}

void	lexer_tok_constructor_new(t_tok_constructor *constructor, int stri)
{
	t_token	*token;

	if (error_get() != SUCCESS)
		return ;
	token = _lexer_token_create();
	constructor->cur_token = token;
	constructor->mode = E_MODE_WORD;
	constructor->start_index = stri;
}

void	lexer_tok_constructor_init(t_tok_constructor *c, const char *str)
{
	if (error_get() != SUCCESS)
		return ;
	c->mode = E_MODE_WORD;
	c->start_index = 0;
	c->cur_token = NULL;
	c->str = str;
}

void	lexer_tok_constructor_free(t_tok_constructor *constructor)
{
	if (constructor->cur_token)
		lexer_free_tokens(&constructor->cur_token);
}
