/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 11:30:25 by tokino            #+#    #+#             */
/*   Updated: 2022/01/26 11:55:39 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	print_node(t_ast_node *n)
{
	int	i;

	if (n->type == E_AST_NODE_TYPE_PIPE)
	{
		printf("AST Node of type PIPE at %p:\n", n);
		printf("Left child is at %p (should not be nil)\n", n->left);
		printf("Right child is at %p (should not be nil)\n", n->right);
	}
	else if (n->type == E_AST_NODE_TYPE_COMMAND)
	{
		printf("AST Node of type COMMAND at %p:\n", n);
		printf("Command arguments : ");
		i = 0;
		while (n->command->args[i] != NULL)
			printf("%s ", n->command->args[i++]);
		printf("\n");
		printf("Command redirections (%d): \n", n->command->redirection_nb);
		i = 0;
		while (i < n->command->redirection_nb)
		{
			printf("    - ");
			if (n->command->redirections[i].type == E_REDIR_TYPE_STDIN)
				printf("< ");
			else if (n->command->redirections[i].type == E_REDIR_TYPE_STDOUT)
				printf("> ");
			else if (n->command->redirections[i].type == E_REDIR_TYPE_APPEND)
				printf(">> ");
			else if (n->command->redirections[i].type == E_REDIR_TYPE_HEREDOC)
				printf("<< ");
			printf("%s \n", n->command->redirections[i].path);
			i++;
		}
		printf("Left child is at %p (should be nil)\n", n->left);
		printf("Right child is at %p (should be nil)\n", n->right);
	}
	printf("\n");
}

void	print_ast(t_ast_node *node, int depth)
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

	msg = "Syntax error near unexpected token ";
	write(2, msg, str_len(msg));
	write(2, token->content, str_len(token->content));
	write(2, "\n", 1);
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
