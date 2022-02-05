/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_n_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 11:41:26 by tokino            #+#    #+#             */
/*   Updated: 2022/02/05 15:19:49 by tokino           ###   ########.fr       */
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
	if (error_get() != SUCCESS)
		return ;
	redirection->type = _get_redirection_type((*token)->content);
	*token = (*token)->next;
	redirection->path = str_dup((*token)->content);
}

static void	_set_arg(t_carg **cargs, t_token *token)
{
	t_carg	*carg;

	if (error_get() != SUCCESS)
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
	int		arg_count; // TO REMOVE with command->args
	int		redir_count;

	if (error_get() != SUCCESS)
		return ;
	arg_count = 0; // TO REMOVE with command->args
	redir_count = 0;
	while (*token && is_command_token((*token)->type) && error_get() == SUCCESS)
	{
		if ((*token)->type == E_TOKEN_TYPE_WORD)
		{
		//	command->args[arg_count] = str_dup((*token)->content); // TO REMOVE with command->args
			_set_arg(&command->cargs, *token);
			arg_count++; // TO REMOVE with command->args
		}
		else if ((*token)->type == E_TOKEN_TYPE_REDIRECTION)
		{
			_set_redirection(&command->redirections[redir_count], token);
			redir_count++;
		}
		if (error_get() == SUCCESS)
			*token = (*token)->next;
	}
}

static void	_get_size_and_check_syntax(t_token **token, t_command *command)
{
	t_token	*start_token;

	if (error_get() != SUCCESS)
		return ;
	start_token = *token;
	command->arg_nb = 0;
	command->redir_nb = 0;
	while (*token && is_command_token((*token)->type) && error_get() == SUCCESS)
	{
		if ((*token)->type == E_TOKEN_TYPE_WORD)
			command->arg_nb++;
		else if ((*token)->type == E_TOKEN_TYPE_REDIRECTION)
		{
			*token = (*token)->next;
			if (!*token || (*token)->type != E_TOKEN_TYPE_WORD)
			{
				print_syntax_error(*token);
				return ;
			}
			command->redir_nb++;
		}
		*token = (*token)->next;
	}
	*token = start_token;
}

void	init_n_command(t_token **token, t_node **n_command, t_node *n_sep)
{
	t_command	*command;

	if (!is_command_token((*token)->type))
	{
		print_syntax_error(*token);
		return ;
	}
	*n_command = n_create(E_NODE_TYPE_COMMAND);
	if (*n_command == NULL)
		return ;
	command = (*n_command)->command;
	_get_size_and_check_syntax(token, command);
	//command->args = uti_calloc(command->arg_nb, sizeof(t_carg));
	command->cargs = NULL;
	command->redirections = uti_calloc(command->redir_nb, sizeof(t_redir));
	_set_n_command(token, command);
	if (n_sep)
		n_sep->right = *n_command;
}
