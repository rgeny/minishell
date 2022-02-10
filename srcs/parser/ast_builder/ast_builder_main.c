/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder_main.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 12:21:43 by tokino            #+#    #+#             */
/*   Updated: 2022/02/10 11:35:07 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdio.h>

static t_ast_constructor	*_init_astc(t_token *tokens, t_env *env)
{
	t_ast_constructor	*astc;

	astc = uti_calloc(1, sizeof(t_ast_constructor));
	astc->tokens = tokens;
	astc->env = env;
	return (astc);
}

void	eat_token(t_ast_constructor *astc, t_token_type type)
{
	if (astc->tokens && astc->tokens->type == type)
		astc->tokens = astc->tokens->next;
	else if (!is_error())
		print_syntax_error(astc->tokens);
}

t_ast	*build_ast(t_token *tokens, t_env *env)
{
	t_ast				*root;
	t_ast_constructor	*astc;

	if (tokens == NULL || is_error())
		return (NULL);
	astc = _init_astc(tokens, env);
	root = build_pipeline_list(astc, false);
	if (!is_error() && astc->tokens)
		print_syntax_error(astc->tokens);
	free(astc);
	return (root);
}
