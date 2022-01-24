/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 12:21:43 by tokino            #+#    #+#             */
/*   Updated: 2022/01/24 21:24:09 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	_print_unspec_msg(char *token)
{
	char *msg;

	msg = " token is unspecified for minishell. Please dont use it\n";
	write(2, "The ", 4);
	write(2, token, str_len(token));
	write(2, msg, str_len(msg));
	return (0);
}

t_ast_node *create_node(t_ast_node_type type)
{
	t_ast_node *node;

	node = malloc(sizeof(t_ast_node));
	if (node == NULL)
		return (NULL); // clean all and exit
	node->type = type;
	node->left = NULL;
	node->right = NULL;
	if (type == E_AST_NODE_TYPE_COMMAND)
	{
		node->command = malloc(sizeof(t_command));
		if (node->command == NULL)
			return (NULL); // Clean all and exit
		node->command->args = NULL;
		node->command->redirections = NULL;
	}
	else
	{
		node->command = NULL;
	}
	return (node);
}

int _get_command_size(t_token *current_token)
{
	int size;

	size = 0;
	while (current_token && (current_token->type == E_TOKEN_TYPE_WORD || current_token->type == E_TOKEN_TYPE_REDIRECTION))
	{
		size++;
		current_token = current_token->next;
	}
	return (size);
}

t_redir_type _get_redirection_type(char *token_content)
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

#include <stdio.h>
void print_node(t_ast_node *node)
{
	if (node->type == E_AST_NODE_TYPE_PIPE)
	{
		printf("AST Node of type PIPE at %p:\n", node);
		printf("Left child is at %p (should not be nil)\n", node->left);
		printf("Right child is at %p (should not be nil)\n", node->right);
	}
	else if (node->type == E_AST_NODE_TYPE_COMMAND)
	{
		printf("AST Node of type COMMAND at %p:\n", node);
		printf("Command arguments : ");
		int i = 0;
		while(node->command->args[i] != NULL)
			printf("%s ", node->command->args[i++]);
		printf("\n");
		printf("Command redirections (%d): \n", node->command->redirection_nb);
		i = 0;
		while(i < node->command->redirection_nb)
		{
			printf("    - ");
			if (node->command->redirections[i].type == E_REDIR_TYPE_STDIN)
				printf("< ");
			else if (node->command->redirections[i].type == E_REDIR_TYPE_STDOUT)
				printf("> ");
			else if (node->command->redirections[i].type == E_REDIR_TYPE_APPEND)
				printf(">> ");
			else if (node->command->redirections[i].type == E_REDIR_TYPE_HEREDOC)
				printf("<< ");
			printf("%s \n", node->command->redirections[i].path);
			i++;
		}
		printf("Left child is at %p (should be nil)\n", node->left);
		printf("Right child is at %p (should be nil)\n", node->right);
	}
	printf("\n");
}

void print_ast(t_ast_node *node, int depth)
{
	if (!node)
		return;
	print_node(node);
	if (node->left)
		print_ast(node->left, depth++);
	if (node->right)
		print_ast(node->right, depth++);
}

int	print_syntax_error(t_token *token)
{
	char *msg;

	msg = "Syntax error near unexpected token ";
	write(2, msg, str_len(msg));
	write(2, token->content, str_len(token->content));
	write(2, "\n", 1);
	return (1);
}

t_ast_node *create_command_node(t_token **current_token)
{
	t_ast_node	*command_node;

	command_node = create_node(E_AST_NODE_TYPE_COMMAND);
	int command_size = _get_command_size(*current_token);
	command_node->command->args = (char **)uti_calloc(command_size + 1, sizeof(char*)); // TODO, alloc only necessary size (here is size of command + redir)
	command_node->command->redirections = (t_redir *)uti_calloc(command_size + 1, sizeof(t_redir)); // TODO, alloc only necessary size (here is size of command + redir)
	// printf("command_size=%d\n", command_size);
	int arg_nb = 0;
	int redir_nb = 0;
	while (arg_nb + redir_nb * 2 < command_size)
	{
		// printf("type: %d, token: %s\n", current_token->type, current_token->content);
		if ((*current_token)->type == E_TOKEN_TYPE_WORD)
		{
			// printf("This token is a arg of a command\n");
			command_node->command->args[arg_nb] = str_ndup((*current_token)->content, str_len((*current_token)->content));
			arg_nb++;
		}
		else if ((*current_token)->type == E_TOKEN_TYPE_REDIRECTION)
		{
			command_node->command->redirections[redir_nb].type = _get_redirection_type((*current_token)->content);
			*current_token = (*current_token)->next;
			// printf("This token is a redirection of a command with path %s\n", (*current_token)->content);
			command_node->command->redirections[redir_nb].path = str_ndup((*current_token)->content, str_len((*current_token)->content));
			redir_nb++;
		}
		*current_token = (*current_token)->next;
	}
	command_node->command->redirection_nb = redir_nb;
	return (command_node);
}

#include <stdio.h>
int	parse_tokens(t_data *data, t_token *tokens)
{
	t_token		*current_token;
	t_ast_node	*command_node;
	t_ast_node	*parent_node;

	current_token = tokens;
	parent_node = NULL;


	// Syntax error if 1st token is not part of a command
	if (current_token->type != E_TOKEN_TYPE_WORD && current_token->type != E_TOKEN_TYPE_REDIRECTION)
		return (print_syntax_error(current_token));

	// printf("type: %d, token: %s\n", current_token->type, current_token->content);
	// TODO : Add syntax error if error inside command (example : redirection without path/limiter)

	command_node = create_command_node(&current_token);

	if (parent_node)
		parent_node->right = command_node;


	
	while(current_token)
	{
		// PIPE NODE
		if (!parent_node)
		{
			parent_node = create_node(E_AST_NODE_TYPE_PIPE);
			parent_node->left = command_node;
		}
		else 
		{
			t_ast_node *new_parent_node;
			new_parent_node = create_node(E_AST_NODE_TYPE_PIPE);
			new_parent_node->left = parent_node;
			parent_node = new_parent_node;
		}
		if (current_token->next) 
		{
			current_token = current_token->next;
			// COMMAND NODE
			// Syntax error if 1st token is not part of a command
			if (current_token->type != E_TOKEN_TYPE_WORD && current_token->type != E_TOKEN_TYPE_REDIRECTION)
				return (print_syntax_error(current_token));

			// printf("type: %d, token: %s\n", current_token->type, current_token->content);
			// TODO : Add syntax error if error inside command (example : redirection without path/limiter)

			command_node = create_command_node(&current_token);

			if (parent_node)
				parent_node->right = command_node;
		}
		else
			return (print_syntax_error(current_token));
	}
	if (parent_node)
		data->ast_root = parent_node;
	else
		data->ast_root = command_node;

	print_ast(data->ast_root, 0);
	return (0);
}