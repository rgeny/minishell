/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_n_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 11:41:26 by tokino            #+#    #+#             */
/*   Updated: 2022/01/30 15:20:13 by tokino           ###   ########.fr       */
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
	else
		return (E_REDIR_TYPE_HEREDOC);
}

static int	_set_redirection(t_redir *redirection, t_token **token)
{
	redirection->type = _get_redirection_type((*token)->content);
	*token = (*token)->next;
	redirection->path = str_dup((*token)->content);
	if (redirection->path == NULL)
		return (MALLOC_ERROR_CODE);
	return (OK);
}

static int	_set_n_command(t_token **token, t_command *command)
{
	int		arg_count;
	int		redir_count;
	t_carg	*carg;

	arg_count = 0;
	redir_count = 0;
	carg = NULL;
	while (arg_count + redir_count < command->arg_nb + command->redir_nb)
	{
		if ((*token)->type == E_TOKEN_TYPE_WORD)
		{
			command->args[arg_count] = str_dup((*token)->content);
			carg = uti_calloc(1, sizeof(t_carg));
			if (carg == NULL)
				return (MALLOC_ERROR_CODE);
			carg->content = str_dup((*token)->content);
			carg->next = NULL;
			if (carg->content == NULL)
				return (MALLOC_ERROR_CODE);
			lst_carg_add_back(&command->cargs, carg);
			arg_count++;
		}
		else if ((*token)->type == E_TOKEN_TYPE_REDIRECTION)
		{
			if (_set_redirection(&command->redirections[redir_count], token))
				return (MALLOC_ERROR_CODE);
			redir_count++;
		}
		*token = (*token)->next;
	}
	return (OK);
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
				return (SYNTAX_ERROR_CODE);
			command->redir_nb++;
		}
		*token = (*token)->next;
	}
	*token = start_token;
	return (OK);
}

int	init_n_command(t_token **token, t_node **n_command, t_node *n_sep)
{
	t_command	*command;

	if (!is_command_token((*token)->type))
		return (SYNTAX_ERROR_CODE);
	*n_command = n_create(E_NODE_TYPE_COMMAND);
	if (*n_command == NULL)
		return (MALLOC_ERROR_CODE);
	command = (*n_command)->command;
	if (_get_size_and_check_syntax(token, command) == SYNTAX_ERROR_CODE)
		return (SYNTAX_ERROR_CODE);
	command->args = uti_calloc(command->arg_nb, sizeof(t_carg));
	command->cargs = NULL;
	command->redirections = uti_calloc(command->redir_nb, sizeof(t_redir));
	if (command->redirections == NULL || command->args == NULL)
		return (MALLOC_ERROR_CODE);
	if (_set_n_command(token, command) == MALLOC_ERROR_CODE)
		return (MALLOC_ERROR_CODE);
	if (n_sep)
		n_sep->right = *n_command;
	return (OK);
}
