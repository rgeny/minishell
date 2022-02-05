/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_n_separator.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 11:49:27 by tokino            #+#    #+#             */
/*   Updated: 2022/02/05 15:16:36 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	init_n_separator(t_node **n_separator, t_node *n_command)
{
	t_node	*new_n_separator;

	new_n_separator = n_create(E_NODE_TYPE_PIPE);
	if (new_n_separator == NULL)
		return ;
	if (!*n_separator)
		new_n_separator->left = n_command;
	else
		new_n_separator->left = *n_separator;
	*n_separator = new_n_separator;
}
