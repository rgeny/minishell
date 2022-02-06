/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_n_separator.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 11:49:27 by tokino            #+#    #+#             */
/*   Updated: 2022/02/06 12:06:11 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	init_n_pipe(t_node **pipe_node, t_node *n_command)
{
	t_node	*new_n_separator;

	new_n_separator = n_create(E_NODE_TYPE_PIPE);
	if (new_n_separator == NULL)
		return ;
	if (!*pipe_node)
		new_n_separator->left = n_command;
	else
		new_n_separator->left = *pipe_node;
	*pipe_node = new_n_separator;
}
