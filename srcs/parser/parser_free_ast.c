/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free_ast.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 17:43:18 by tokino            #+#    #+#             */
/*   Updated: 2022/02/09 12:18:10 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	free_cargs(t_carg *cargs)
{
	t_carg	*tmp;

	while (cargs != NULL)
	{
		tmp = cargs;
		cargs = cargs->next;
		free(tmp->content);
		free(tmp);
	}
}

void	free_redirections(t_command *command)
{
	int		i;
	t_redir	*redir;

	i = 0;
	while (i < command->redir_nb)
	{
		redir = &command->redirections[i];
		free(redir->path);
		i++;
	}
	free(command->redirections);
}

void	free_n_command(t_command *command)
{
	if (command->cargs)
	{
		free_cargs(command->cargs);
		command->cargs = NULL;
	}
	if (command->redirections)
	{
		free_redirections(command);
		command->redirections = NULL;
	}
	free(command);
}

void	free_ast(t_node **root)
{
	if (!*root)
		return ;
	if ((*root)->left)
		free_ast(&(*root)->left);
	if ((*root)->right)
		free_ast(&(*root)->right);
	if ((*root)->cmd)
	{
		free_n_command((*root)->cmd);
		(*root)->cmd = NULL;
	}
	free(*root);
	*root = NULL;
}
