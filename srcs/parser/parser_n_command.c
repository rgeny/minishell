/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_n_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 11:41:26 by tokino            #+#    #+#             */
/*   Updated: 2022/01/26 11:52:01 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_redir_type	_get_redirection_type(char *token_content)
{
	if (!str_cmp(token_content, "<"))
		return (E_REDIR_TYPE_STDIN);
	else if (!str_cmp(token_content, ">"))
		return (E_REDIR_TYPE_STDOUT);
	else if (!str_cmp(token_content, ">>"))
		return (E_REDIR_TYPE_APPEND);
	else //if (!str_cmp(token_content, "<<"))
		return (E_REDIR_TYPE_HEREDOC);
}

static int	_get_command_size(t_token *current_token)
{
	int	size;

	size = 0;
	while (current_token && is_command_token(current_token->type))
	{
		size++;
		current_token = current_token->next;
	}
	return (size);
}

static int	_set_n_command(t_token **current_token, t_command *command)
{
	int command_size = _get_command_size(*current_token);
	command->args = (char **)uti_calloc(command_size + 1, sizeof(char*)); // TODO, alloc only necessary size (here is size of command + redir)
	command->redirections = (t_redir *)uti_calloc(command_size + 1, sizeof(t_redir)); // TODO, alloc only necessary size (here is size of command + redir)
	int arg_nb = 0;
	int redir_nb = 0;
	while (arg_nb + redir_nb * 2 < command_size)
	{
		if ((*current_token)->type == E_TOKEN_TYPE_WORD)
		{
			command->args[arg_nb] = str_dup((*current_token)->content);
			arg_nb++;
		}
		else if ((*current_token)->type == E_TOKEN_TYPE_REDIRECTION)
		{
			command->redirections[redir_nb].type = _get_redirection_type((*current_token)->content);
			*current_token = (*current_token)->next;
			command->redirections[redir_nb].path = str_dup((*current_token)->content);
			redir_nb++;
		}
		*current_token = (*current_token)->next;
	}
	command->redirection_nb = redir_nb;
	return (0);
}

int	create_and_set_n_command(t_token **current_token, t_ast_node **n_command, t_ast_node *n_separator)
{
	if (!is_command_token((*current_token)->type))
		return (1); // Error : command start by a separator (case of several separator in a row)

	// printf("type: %d, token: %s\n", current_token->type, current_token->content);
	// TODO : Add syntax error if error inside command (example : redirection without path/limiter)

	*n_command = n_create(E_AST_NODE_TYPE_COMMAND);
	_set_n_command(current_token, (*n_command)->command);
	if (n_separator)
		n_separator->right = *n_command;
	return (0);
}
