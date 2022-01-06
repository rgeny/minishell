/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_free_tokens.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 10:11:21 by tokino            #+#    #+#             */
/*   Updated: 2022/01/06 11:28:51 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	lexer_free_tokens(t_token **tokens)
{
	t_token	*next_token;
	t_token	*cur_token;

	cur_token = *tokens;
	while (cur_token)
	{
		next_token = cur_token->next;
		if (cur_token->content)
			free(cur_token->content);
		free(cur_token);
		cur_token = next_token;
	}
	*tokens = NULL;
}
