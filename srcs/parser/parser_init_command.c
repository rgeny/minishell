/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 11:41:26 by tokino            #+#    #+#             */
/*   Updated: 2022/02/08 14:38:05 by tokino           ###   ########.fr       */
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

static void	_set_redirection(t_redir *redirection, t_token **token)
{
	if (is_error())
		return ;
	redirection->type = _get_redirection_type((*token)->content);
	*token = (*token)->next;
	redirection->path = str_dup((*token)->content);

	//process heredoc
}

static void	_set_arg(t_carg **cargs, t_token *token)
{
	t_carg	*carg;

	if (is_error())
		return ;
	carg = uti_calloc(1, sizeof(t_carg));
	if (carg == NULL)
		return ;
	carg->content = str_dup(token->content);
	carg->next = NULL;
	lst_carg_add_back(cargs, carg);
}

static void	_set_n_command(t_token **token, t_command *command)
{
	int		redir_count;

	if (is_error())
		return ;
	redir_count = 0;
	while (!is_error() && is_command_token(*token))
	{
		if ((*token)->type == E_TOKEN_TYPE_WORD)
		{
			_set_arg(&command->cargs, *token);
		}
		else if ((*token)->type == E_TOKEN_TYPE_REDIRECTION)
		{
			_set_redirection(&command->redirections[redir_count], token);
			redir_count++;
		}
		if (!is_error())
			*token = (*token)->next;
	}
}

static void	_get_size_and_check_syntax(t_token **token, t_command *command)
{
	t_token	*current_token;

	if (is_error())
		return ;
	current_token = *token;
	command->arg_nb = 0;
	command->redir_nb = 0;
	while (!is_error() && is_command_token(current_token))
	{
		if (current_token->type == E_TOKEN_TYPE_WORD)
			command->arg_nb++;
		else if (current_token->type == E_TOKEN_TYPE_REDIRECTION)
		{
			current_token = current_token->next;
			if (!current_token || current_token->type != E_TOKEN_TYPE_WORD)
			{
				print_syntax_error(current_token);
				return ;
			}
			command->redir_nb++;
		}
		current_token = current_token->next;
	}
}

t_node	*init_command(t_token **tokens)
{
	t_command	*command;
	t_node		*command_node;

	if (is_error())
		return (NULL);
	if (is_opened_parenthesis_token(*tokens))
	{
		*tokens = (*tokens)->next; // OPENED_PAR
		command_node = init_pipeline_list(tokens, true);
		*tokens = (*tokens)->next; // CLOSED_PAR
	}
	else
	{
		if (!is_command_token(*tokens))
		{
			print_syntax_error(*tokens);
			return (NULL);
		}
		command_node = create_node(E_NODE_TYPE_COMMAND);
		if (command_node == NULL)
			return (NULL);
		command = command_node->command;
		_get_size_and_check_syntax(tokens, command);
		command->cargs = NULL;
		command->redirections = uti_calloc(command->redir_nb, sizeof(t_redir));
		_set_n_command(tokens, command);
	}
	return (command_node);
}
