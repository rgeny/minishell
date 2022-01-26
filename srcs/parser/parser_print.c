/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 11:30:25 by tokino            #+#    #+#             */
/*   Updated: 2022/01/26 17:44:07 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	_print_command(t_command *command)
{
	int	i;

	i = 0;
	printf("Command arguments (%d): ", command->arg_nb);
	while (command->args[i] != NULL)
		printf("%s ", command->args[i++]);
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
	int	i;

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

int	print_syntax_error(t_token *token)
{
	char	*msg;

	msg = "Syntax error near unexpected token '";
	write(2, msg, str_len(msg));
	if (token)
		write(2, token->content, str_len(token->content));
	else
		write(2, "newline", 7);
	write(2, "'\n", 2);
	return (1);
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
