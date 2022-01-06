/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_get_char_type.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 09:39:05 by tokino            #+#    #+#             */
/*   Updated: 2022/01/06 11:28:50 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	lexer_get_chartype(char c)
{
	if (uti_is_in_charset(c, " \t"))
		return (E_CHAR_TYPE_BLANK);
	else if (c == '\'')
		return (E_CHAR_TYPE_SQUOTE);
	else if (c == '"')
		return (E_CHAR_TYPE_DQUOTE);
	else if (uti_is_in_charset(c, "<>|&"))
		return (E_CHAR_TYPE_OPERATOR);
	else
		return (E_CHAR_TYPE_ALNUMP);
}
