/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_lexer.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 13:11:07 by buschiix          #+#    #+#             */
/*   Updated: 2022/02/06 14:50:01 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_LEXER_H
# define T_LEXER_H
typedef enum e_token_type {
	E_TOKEN_TYPE_WORD,
	E_TOKEN_TYPE_OPERATOR,
	E_TOKEN_TYPE_REDIRECTION,
	E_TOKEN_TYPE_PIPE,
	E_TOKEN_TYPE_OR,
	E_TOKEN_TYPE_AND,
	E_TOKEN_TYPE_PARENTHESIS_OPEN,
	E_TOKEN_TYPE_PARENTHESIS_CLOSE
}	t_token_type;

typedef struct s_token {
	char			*content;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

#endif
