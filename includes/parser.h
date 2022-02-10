/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 12:22:51 by tokino            #+#    #+#             */
/*   Updated: 2022/02/10 11:20:21 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>

# include "t_ast.h"
# include "str.h"
# include "utils.h"
# include "lst.h"
# include "error.h"
# include "expander.h"

int		parser_main(t_data *data, char *rl);

t_ast	*build_ast(t_token *tokens, t_env *env);
t_ast	*build_command(t_ast_constructor *astc);
t_ast	*build_pipeline(t_ast_constructor *astc);
t_ast	*build_pipeline_list(t_ast_constructor *astc, bool is_subshell);
t_ast	*create_node(t_node_type type);
void	eat_token(t_ast_constructor *astc, t_token_type type);
void	print_ast(t_ast *root);
void	free_ast(t_ast **root);
int		print_syntax_error(t_token *token);
bool	is_command_token(t_token *token);
bool	is_opened_parenthesis_token(t_token *token);
bool	is_closed_parenthesis_token(t_token *token);

#endif
