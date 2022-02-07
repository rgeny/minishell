/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 12:22:51 by tokino            #+#    #+#             */
/*   Updated: 2022/02/07 17:23:54 by tokino           ###   ########.fr       */
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

t_node	*n_create(t_node_type type);
t_node	*init_command(t_token **token);
t_node	*init_pipeline(t_token **token);
t_node	*init_pipeline_list(t_token **tokens, bool is_subshell);
t_node	*init_separator_node(
			t_token *token, t_node *sep_node, t_node *cmd_node);

bool	is_command_token(t_token *token);
bool	is_pipeline_token(t_token *token);
bool	is_list_token(t_token *token);
bool	is_opened_parenthesis_token(t_token *token);
bool	is_closed_parenthesis_token(t_token *token);

int		print_syntax_error(t_token *token);
void	print_ast(t_node *root);
void	free_ast(t_node **root);

#endif
