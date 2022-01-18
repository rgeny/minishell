/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 18:12:18 by tokino            #+#    #+#             */
/*   Updated: 2022/01/18 14:34:39 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	_token_add_back(t_token **tokens, t_token *token)
{
	t_token	*current_token;

	current_token = *tokens;
	while (current_token && current_token->next)
		current_token = current_token->next;
	if (current_token)
		current_token->next = token;
	else
		*tokens = token;
}

static t_token_type _get_ope_token_type(t_token *token)
{
	if (uti_is_in_charset(token->content[0], "<>"))
		return (E_TOKEN_TYPE_REDIRECTION);
	else if (!str_cmp(token->content, "|"))
		return (E_TOKEN_TYPE_PIPE);
	else if (!str_cmp(token->content, "||"))
		return (E_TOKEN_TYPE_OR);
	else if (!str_cmp(token->content, "&&"))
		return (E_TOKEN_TYPE_AND);
	else
		return (E_TOKEN_TYPE_OPERATOR);
}

int	lexer_create_operator_token(t_tok_constructor *constructor, t_token **tokens, int stri)
{
	int			len;
	const char	*str;

	str = constructor->str;
	if (uti_is_in_charset(str[stri], "<>&|") && str[stri] == str[stri + 1])
		len = 2;
	else
		len = 1;
	constructor->cur_token->content = str_ndup(&str[stri], len);
	constructor->cur_token->type = _get_ope_token_type(constructor->cur_token);
	_token_add_back(tokens, constructor->cur_token);
	return (len);
}

int	lexer_terminate_token(t_tok_constructor *constructor, t_token **tokens, int stri)
{
	int		token_len;
	char	*str_start;

	if (stri == constructor->start_index)
	{
		constructor->start_index++;
		return (1);
	}
	str_start = (char *)constructor->str + constructor->start_index;
	token_len = stri - constructor->start_index;
	constructor->cur_token->content = str_ndup(str_start, token_len);
	constructor->cur_token->type = E_TOKEN_TYPE_WORD;
	_token_add_back(tokens, constructor->cur_token);
	constructor->cur_token = NULL;
	return (1);
}

int	lexer_update_token_mode(t_tok_constructor *constructor, char c)
{
	if (constructor->mode == E_MODE_WORD)
	{
		if (lexer_get_chartype(c) == E_CHAR_TYPE_SQUOTE)
			constructor->mode = E_MODE_SQUOTE;
		else if (lexer_get_chartype(c) == E_CHAR_TYPE_DQUOTE)
			constructor->mode = E_MODE_DQUOTE;
	}
	else if (constructor->mode == E_MODE_DQUOTE && \
				lexer_get_chartype(c) == E_CHAR_TYPE_DQUOTE)
		constructor->mode = E_MODE_WORD;
	else if (constructor->mode == E_MODE_SQUOTE && \
				lexer_get_chartype(c) == E_CHAR_TYPE_SQUOTE)
		constructor->mode = E_MODE_WORD;
	return (1);
}
