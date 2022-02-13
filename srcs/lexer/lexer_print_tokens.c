/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_print_tokens.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 18:20:33 by tokino            #+#    #+#             */
/*   Updated: 2022/02/13 17:25:50 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	lexer_print_tokens(t_token *token)
{
	if (is_error() || !token)
		return ;
	printf("\nTokens:\n");
	while (token)
	{
		printf("Type:%d, content:%s\n", token->type, token->content);
		token = token->next;
	}
	printf("\n");
	return ;
}
