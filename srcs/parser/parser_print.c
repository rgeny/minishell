/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 11:30:25 by tokino            #+#    #+#             */
/*   Updated: 2022/01/30 17:28:40 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	_print_command(t_command *command)
{
	int		i;
	t_carg	*carg;

	i = 0;
	printf("Command arguments (%d): ", command->arg_nb);
	carg = command->cargs;
	while (carg)
	{
		printf("%s ", carg->content);
		carg = carg->next;
	}
	printf("\n");
	printf("Command redirections (%d): \n", command->redir_nb);
	i = 0;
	while (i < command->redir_nb)
	{
		printf("    - ");
		if (command->redirections[i].type == E_REDIR_TYPE_STDIN)
			printf("< ");
		else if (command->redirections[i].type == E_REDIR_TYPE_STDOUT)
			printf("> ");
		else if (command->redirections[i].type == E_REDIR_TYPE_APPEND)
			printf(">> ");
		else if (command->redirections[i].type == E_REDIR_TYPE_HEREDOC)
			printf("<< ");
		printf("%s \n", command->redirections[i].path);
		i++;
	}
}

void	print_node(t_node *n)
{
	if (n->type == E_NODE_TYPE_PIPE)
	{
		printf("AST Node of type PIPE at %p:\n", n);
		printf("Left child is at %p (should not be nil)\n", n->left);
		printf("Right child is at %p (should not be nil)\n", n->right);
	}
	else if (n->type == E_NODE_TYPE_COMMAND)
	{
		printf("AST Node of type COMMAND at %p:\n", n);
		_print_command(n->command);
		printf("Left child is at %p (should be nil)\n", n->left);
		printf("Right child is at %p (should be nil)\n", n->right);
	}
	printf("\n");
}

void	print_ast(t_node *node, int depth)
{
	if (!node)
		return ;
	print_node(node);
	if (node->left)
		print_ast(node->left, depth++);
	if (node->right)
		print_ast(node->right, depth++);
}

int	print_syntax_error(t_data *data, t_token *token)
{
	char	*msg;
	char	*token_content;

	msg = "Syntax error near unexpected token '";
	if (token)
		token_content = token->content;
	else
		token_content = "newline";
	print_error(msg, token_content, "'\n", data);
	return (1);
}

int print_parser_error(t_data *data, int error_code, t_token *token)
{
	if (error_code == SYNTAX_ERROR_CODE)
	{
		print_syntax_error(data, token);
	}
	else if (error_code == MALLOC_ERROR_CODE)
	{
		print_error("Cannot allocate memory\n", NULL, NULL, data);
	}
	return (error_code);
} 

int	print_unspec_msg(char *token)
{
	char	*msg;

	msg = " token is unspecified for minishell. Please dont use it\n";
	write(2, "The ", 4);
	write(2, token, str_len(token));
	write(2, msg, str_len(msg));
	return (1);
}
