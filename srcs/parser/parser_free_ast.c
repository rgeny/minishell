/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free_ast.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 17:43:18 by tokino            #+#    #+#             */
/*   Updated: 2022/02/10 08:42:07 by rgeny            ###   ########.fr       */
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
		str_free(tmp->content);
		free(tmp);
	}
}

void	free_redirections(t_redir *redirections)
{
	t_redir	*tmp;

	while (redirections != NULL)
	{
		tmp = redirections;
		redirections = redirections->next;
		free(tmp->path);
		free(tmp);
	}
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
		free_redirections(command->redirections);
		command->redirections = NULL;
	}
	free(command);
}

void	free_ast(t_ast **root)
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
