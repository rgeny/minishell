/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 12:21:43 by tokino            #+#    #+#             */
/*   Updated: 2022/01/30 17:41:50 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	is_command_token(t_token_type type)
{
	return (type == E_TOKEN_TYPE_WORD || type == E_TOKEN_TYPE_REDIRECTION);
}

static void	_set_root(t_data *data, t_node *n_command, t_node *n_separator)
{
	if (n_separator)
		data->ast_root = n_separator;
	else
		data->ast_root = n_command;
}

int	parse_tokens(t_data *data, t_token *tokens)
{
	t_token	*current_token;
	t_node	*n_command;
	t_node	*n_separator;
	int ret;

	current_token = tokens;
	n_separator = NULL;
	ret = init_n_command(&current_token, &n_command, n_separator);
	if (ret)
		return (print_parser_error(data, ret, current_token));
	while (current_token)
	{
		ret = init_n_separator(&n_separator, n_command);
		if (ret)
			return (print_parser_error(data, ret, current_token));
		if (!current_token->next)
			return (print_parser_error(data, 1, current_token));
		current_token = current_token->next;
		ret = init_n_command(&current_token, &n_command, n_separator);
		if (ret)
			return (print_parser_error(data, ret, current_token));
	}
	_set_root(data, n_command, n_separator);
	return (OK);
}
