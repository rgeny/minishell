/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 11:41:26 by tokino            #+#    #+#             */
/*   Updated: 2022/02/08 14:53:55 by tokino           ###   ########.fr       */
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

static void	_set_redirection(t_redir *redirection, t_ast_constructor *astc)
{
	if (is_error())
		return ;
	redirection->type = _get_redirection_type(astc->tokens->content);
	astc->tokens = astc->tokens->next;
	redirection->path = str_dup(astc->tokens->content);

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

static void	_set_n_command(t_ast_constructor *astc, t_command *command)
{
	int		redir_count;

	if (is_error())
		return ;
	redir_count = 0;
	while (!is_error() && is_command_token(astc->tokens))
	{
		if (astc->tokens->type == E_TOKEN_TYPE_WORD)
		{
			_set_arg(&command->cargs, astc->tokens);
		}
		else if (astc->tokens->type == E_TOKEN_TYPE_REDIRECTION)
		{
			_set_redirection(&command->redirections[redir_count], astc);
			redir_count++;
		}
		if (!is_error())
			astc->tokens = astc->tokens->next;
	}
}

static void	_get_size_and_check_syntax(t_ast_constructor *astc, t_command *command)
{
	t_token	*current_token;

	if (is_error())
		return ;
	current_token = astc->tokens;
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

t_node	*init_command(t_ast_constructor *astc)
{
	t_command	*command;
	t_node		*command_node;

	if (is_error())
		return (NULL);
	if (is_opened_parenthesis_token(astc->tokens))
	{
		astc->tokens = astc->tokens->next; // OPENED_PAR
		command_node = init_pipeline_list(astc, true);
		astc->tokens = astc->tokens->next; // CLOSED_PAR
	}
	else
	{
		if (!is_command_token(astc->tokens))
		{
			print_syntax_error(astc->tokens);
			return (NULL);
		}
		command_node = create_node(E_NODE_TYPE_COMMAND);
		if (command_node == NULL)
			return (NULL);
		command = command_node->command;
		_get_size_and_check_syntax(astc, command);
		command->cargs = NULL;
		command->redirections = uti_calloc(command->redir_nb, sizeof(t_redir));
		_set_n_command(astc, command);
	}
	return (command_node);
}
