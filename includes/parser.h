/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 12:22:51 by tokino            #+#    #+#             */
/*   Updated: 2022/01/26 11:50:02 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>

# include "struct.h"
# include "str.h"
# include "utils.h"

int	parse_tokens(t_data *data, t_token *tokens);

t_ast_node *n_create(t_ast_node_type type);
int	create_and_set_n_command(t_token **current_token, t_ast_node **n_command, t_ast_node *n_separator);
int	create_and_set_n_separator(t_ast_node **n_separator, t_ast_node *n_command);

bool is_command_token(t_token_type type);

int	print_unspec_msg(char *token);
void print_node(t_ast_node *n);
void print_ast(t_ast_node *node, int depth);
int	print_syntax_error(t_token *token);

#endif
