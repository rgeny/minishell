/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 12:22:51 by tokino            #+#    #+#             */
/*   Updated: 2022/02/08 15:14:39 by tokino           ###   ########.fr       */
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

int		parser_main(t_data *data, char *rl);
t_node	*parse_tokens(t_token *tokens);

t_node	*create_node(t_node_type type);
t_node	*init_command(t_ast_constructor *astc);
t_node	*init_pipeline(t_ast_constructor *astc);
t_node	*init_pipeline_list(t_ast_constructor *astc, bool is_subshell);
void	eat_token(t_ast_constructor *astc, t_token_type type);

bool	is_command_token(t_token *token);
bool	is_pipeline_token(t_token *token);
bool	is_list_token(t_token *token);
bool	is_opened_parenthesis_token(t_token *token);
bool	is_closed_parenthesis_token(t_token *token);

int		print_syntax_error(t_token *token);
void	print_ast(t_node *root);
void	free_ast(t_node **root);

#endif
