/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_n_separator.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 11:49:27 by tokino            #+#    #+#             */
/*   Updated: 2022/01/26 11:49:46 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	create_and_set_n_separator(t_ast_node **n_separator, t_ast_node *n_command)
{
	t_ast_node	*new_n_separator;

	new_n_separator = n_create(E_AST_NODE_TYPE_PIPE);
	if (!*n_separator)
		new_n_separator->left = n_command;
	else
		new_n_separator->left = *n_separator;
	*n_separator = new_n_separator;
	return (0);
}
