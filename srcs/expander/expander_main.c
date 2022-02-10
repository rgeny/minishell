/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 16:54:37 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/10 11:02:24 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void	expand_args(t_command *cmd, t_carg *args, t_data *data)
{
	t_carg	*prev;
	t_carg	*next;
	
	prev = NULL;
	cmd->arg_nb = 0;
	while (args)
	{
		if (expand_var(&args->content, data))
		{
			cmd->arg_nb++;
			expand_space_carg(args);
			expand_asterisk(cmd, args, NULL);
			expand_quote(args->content);
			prev = args;
			args = args->next;
		}
		else
			lst_del_one(&args, cmd);
	}
}

void	expand_redir(t_command *cmd, t_redir *redir, t_data *data)
{
	char	*save;

//	while (redir)
//	{
		if (redir->type != E_REDIR_TYPE_HEREDOC)
		{
			save = str_dup(redir->path);
			if (expand_var(&redir->path, data) && expand_space_redir(redir))
			{
				str_free(save);
				expand_asterisk(NULL, NULL, redir);
				expand_quote(redir->path);
			}
			else
			{
				str_free(redir->path);
				redir->path = save;
				error_print(save, REDIR_AMBIGUE, NULL, ERROR_EXEC);
			}
		}
		redir = redir->next;
//	}
}

void	expander_main(t_data *data, t_ast *ast)
{
	if (ast->cmd)
	{
		expand_args(ast->cmd, ast->cmd->cargs, data);
		expand_redir(ast->cmd, ast->cmd->redirections, data);
	}
}
