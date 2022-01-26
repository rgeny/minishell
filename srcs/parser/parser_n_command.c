/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_n_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 11:41:26 by tokino            #+#    #+#             */
/*   Updated: 2022/01/26 17:09:34 by tokino           ###   ########.fr       */
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

static int	_set_redirection(t_redir *redirection, t_token **token)
{
	redirection->type = _get_redirection_type((*token)->content);
	*token = (*token)->next;
	redirection->path = str_dup((*token)->content);
	if (redirection->path == NULL)
		return (2);
	return (0);
}

static int	_set_n_command(t_token **token, t_command *command)
{
	int	arg_count;
	int	redir_count;

	arg_count = 0;
	redir_count = 0;
	while (arg_count + redir_count < command->arg_nb + command->redir_nb)
	{
		if ((*token)->type == E_TOKEN_TYPE_WORD)
		{
			command->args[arg_count] = str_dup((*token)->content);
			if (command->args[arg_count] == NULL)
				return (2);
			arg_count++;
		}
		else if ((*token)->type == E_TOKEN_TYPE_REDIRECTION)
		{
			if (_set_redirection(&command->redirections[redir_count], token))
				return (2);
			redir_count++;
		}
		*token = (*token)->next;
	}
	return (0);
}

static int	_get_size_and_check_syntax(t_token **token, t_command *command)
{
	t_token	*start_token;

	start_token = *token;
	command->arg_nb = 0;
	command->redir_nb = 0;
	while (*token && is_command_token((*token)->type))
	{
		if ((*token)->type == E_TOKEN_TYPE_WORD)
			command->arg_nb++;
		else if ((*token)->type == E_TOKEN_TYPE_REDIRECTION)
		{
			*token = (*token)->next;
			if (!*token || (*token)->type != E_TOKEN_TYPE_WORD)
				return (1);
			command->redir_nb++;
		}
		*token = (*token)->next;
	}
	*token = start_token;
	return (0);
}

int	create_and_set_n_command(t_token **token, t_ast_node **n_command, t_ast_node *n_separator)
{
	t_command	*command;

	if (!is_command_token((*token)->type))
		return (1); // Error : command start by a separator (several separator in a row)
	*n_command = n_create(E_AST_NODE_TYPE_COMMAND);
	command = (*n_command)->command;
	if (_get_size_and_check_syntax(token, command))
		return (1); // Error : redirection without path or limiter
	command->args = uti_calloc(command->arg_nb + 1, sizeof(char *));
	command->redirections = uti_calloc(command->redir_nb, sizeof(t_redir));
	_set_n_command(token, command);
	if (n_separator)
		n_separator->right = *n_command;
	return (0);
}
