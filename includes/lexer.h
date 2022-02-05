/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 10:48:21 by tokino            #+#    #+#             */
/*   Updated: 2022/02/05 18:32:20 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdlib.h>
# include <stdio.h>

# include "t_lexer.h"
# include "str.h"
# include "utils.h"
# include "error.h"

typedef enum e_mode {
	E_MODE_WORD,
	E_MODE_DQUOTE,
	E_MODE_SQUOTE
}	t_mode;

enum e_char_type {
	E_CHAR_TYPE_BLANK,
	E_CHAR_TYPE_ALNUMP,
	E_CHAR_TYPE_DQUOTE,
	E_CHAR_TYPE_SQUOTE,
	E_CHAR_TYPE_OPERATOR
};

typedef struct s_token_constructor {
	t_mode		mode;
	const char	*str;
	int			start_index;
	t_token		*cur_token;
}	t_tok_constructor;

t_token	*lexer_lex(const char *str);
int		lexer_create_operator_tok(
			t_tok_constructor *c, t_token **tokens, int stri);
void		lexer_terminate_token(t_tok_constructor *c, t_token **tokens, int stri);
int		lexer_update_token_mode(t_tok_constructor *constructor, char c);
int		lexer_print_tokens(t_token *token);
void	lexer_tok_constructor_new(t_tok_constructor *c, int start_idx);
void	lexer_tok_constructor_init(t_tok_constructor *c, const char *str);
int		lexer_get_chartype(char c);
void	lexer_tok_constructor_free(t_tok_constructor *constructor);
void	*lexer_free_tokens(t_token **tokens);

#endif
