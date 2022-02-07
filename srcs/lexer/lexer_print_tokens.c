/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_print_tokens.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 18:20:33 by tokino            #+#    #+#             */
/*   Updated: 2022/02/07 15:15:21 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	lexer_print_tokens(t_token *token)
{
	if (is_error())
		return ;
	printf("\nHere is the token list :\n");
	while (token)
	{
		printf("Type:%d, content:%s\n", token->type, token->content);
		token = token->next;
	}
	printf("\n\n");
	return ;
}
