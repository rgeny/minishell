/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_print_tokens.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 18:20:33 by tokino            #+#    #+#             */
/*   Updated: 2022/02/07 11:32:28 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	lexer_print_tokens(t_token *token)
{
	if (error_get() != SUCCESS)
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
