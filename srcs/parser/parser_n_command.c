/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_n_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 11:41:26 by tokino            #+#    #+#             */
/*   Updated: 2022/01/26 15:01:04 by tokino           ###   ########.fr       */
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

static int	_set_n_command(t_token **current_token, t_command *command)
{
	int command_size;
	int arg_count;
	int redir_count;


	arg_count = 0;
	redir_count = 0;
	while (arg_count + redir_count < command->arg_nb + command->redirection_nb)
	{
		if ((*current_token)->type == E_TOKEN_TYPE_WORD)
		{
			command->args[arg_count] = str_dup((*current_token)->content);
			arg_count++;
		}
		else if ((*current_token)->type == E_TOKEN_TYPE_REDIRECTION)
		{
			command->redirections[redir_count].type = _get_redirection_type((*current_token)->content);
			*current_token = (*current_token)->next;
			command->redirections[redir_count].path = str_dup((*current_token)->content);
			redir_count++;
		}
		*current_token = (*current_token)->next;
	}
	return (0);
}

static int	_preset_n_command(t_token **current_token, t_command *command)
{
	// Calcul arg and redirection nb
	// raise syntax error if redir without word
	t_token *start_token;

	start_token = *current_token;
	command->arg_nb = 0;
	command->redirection_nb = 0;
	while (*current_token && is_command_token((*current_token)->type))
	{
		if ((*current_token)->type == E_TOKEN_TYPE_WORD)
			command->arg_nb++;
		else if ((*current_token)->type == E_TOKEN_TYPE_REDIRECTION)
		{
			*current_token = (*current_token)->next;
			if (!*current_token || (*current_token)->type != E_TOKEN_TYPE_WORD)
				return (1);
			command->redirection_nb++;
		}
		*current_token = (*current_token)->next;
	}
	*current_token = start_token;
	return (0);
}

int	create_and_set_n_command(t_token **current_token, t_ast_node **n_command, t_ast_node *n_separator)
{
	t_command *command;
	
	if (!is_command_token((*current_token)->type))
		return (1); // Error : command start by a separator (case of several separator in a row)
	*n_command = n_create(E_AST_NODE_TYPE_COMMAND);
	if (_preset_n_command(current_token, (*n_command)->command))
		return (1);
	command->args = (char **)uti_calloc(command->arg_nb + 1, sizeof(char*)); // TODO, alloc only necessary size (here is size of command + redir)
	command->redirections = (t_redir *)uti_calloc(command->redirection_nb, sizeof(t_redir)); // TODO, alloc only necessary size (here is size of command + redir)
	_set_n_command(current_token, (*n_command)->command);
	if (n_separator)
		n_separator->right = *n_command;
	return (0);
}
