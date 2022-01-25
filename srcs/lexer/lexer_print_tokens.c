/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_print_tokens.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 18:20:33 by tokino            #+#    #+#             */
/*   Updated: 2022/01/25 13:10:38 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	lexer_print_tokens(t_token *token)
{
	printf("\nHere is the token list :\n");
	while (token)
	{
		printf("Type: %d, content: %-6.6s, token: %14p, prev: %14p, next: %14p\n", token->type, token->content, token, token->prev, token->next);
		token = token->next;
	}
	printf("\n\n");
	return (0);
}
