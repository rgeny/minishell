/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 11:41:26 by tokino            #+#    #+#             */
/*   Updated: 2022/02/09 14:48:29 by tokino           ###   ########.fr       */
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

static void	_set_redirection(t_redir **redirections, t_ast_constructor *astc)
{
	t_redir	*redirection;
	t_token	*token;

	if (is_error())
		return ;
	token = astc->tokens;
	eat_token(astc, E_TOKEN_TYPE_REDIRECTION);
	if (is_error())
		return ;
	redirection = uti_calloc(1, sizeof(t_redir));
	if (redirection == NULL)
		return ;
	redirection->type = _get_redirection_type(token->content);
	token = astc->tokens;
	eat_token(astc, E_TOKEN_TYPE_WORD);
	if (is_error())
		return ;
	redirection->path = str_dup(token->content);
	redirection->next = NULL;
	lst_redirection_add_back(redirections, redirection);

	//process heredoc
}

static void	_set_arg(t_ast_constructor *astc, t_carg **cargs)
{
	t_carg	*carg;
	t_token	*token;

	if (is_error())
		return ;
	token = astc->tokens;
	eat_token(astc, E_TOKEN_TYPE_WORD);
	if (is_error())
		return ;
	carg = uti_calloc(1, sizeof(t_carg));
	if (carg == NULL)
		return ;
	carg->content = str_dup(token->content);
	carg->next = NULL;
	lst_carg_add_back(cargs, carg);
}

static void	_set_command(t_ast_constructor *astc, t_command *command)
{
	if (is_error())
		return ;
	while (!is_error() && is_command_token(astc->tokens))
	{
		if (astc->tokens->type == E_TOKEN_TYPE_WORD)
		{
			_set_arg(astc, &command->cargs);
		}
		else if (astc->tokens->type == E_TOKEN_TYPE_REDIRECTION)
		{
			_set_redirection(&command->redirections, astc);
		}
	}
}

t_ast	*build_command(t_ast_constructor *astc)
{
	t_ast		*command_node;

	if (is_error())
		return (NULL);
	if (is_opened_parenthesis_token(astc->tokens))
	{
		eat_token(astc, E_TOKEN_TYPE_OPENED_PAR);
		command_node = build_pipeline_list(astc, true);
		eat_token(astc, E_TOKEN_TYPE_CLOSED_PAR);
	}
	else
	{
		if (!is_command_token(astc->tokens))
			print_syntax_error(astc->tokens);
		command_node = create_node(E_NODE_TYPE_COMMAND);
		if (command_node == NULL)
			return (NULL);
		_set_command(astc, command_node->cmd);
	}
	return (command_node);
}
