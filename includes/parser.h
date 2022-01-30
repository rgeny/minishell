/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 12:22:51 by tokino            #+#    #+#             */
/*   Updated: 2022/01/30 13:46:07 by tokino           ###   ########.fr       */
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

# define OK 0
# define SYNTAX_ERROR_CODE 1
# define MALLOC_ERROR_CODE 2

int	parse_tokens(t_data *data, t_token *tokens);

t_node *n_create(t_node_type type);
int	init_n_command(t_token **current_token, t_node **n_command, t_node *n_separator);
int	init_n_separator(t_node **n_separator, t_node *n_command);

bool is_command_token(t_token_type type);

int	print_unspec_msg(char *token);
void print_node(t_node *n);
void print_ast(t_node *node, int depth);
int	print_syntax_error(t_token *token);

#endif
