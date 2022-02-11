/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 12:39:00 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/11 17:25:35 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void	expand_redir(t_command *cmd, t_redir *redir, t_data *data)
{
	char	*save;

	if (redir->type != E_REDIR_TYPE_HEREDOC)
	{
		save = str_dup(redir->path);
		if (expand_var(&redir->path, data->env, false)
			&& expand_space_redir(redir))
		{
			str_free(&save);
			if (str_len(redir->path) != str_clen(redir->path, '*'))
				expand_asterisk(NULL, NULL, redir);
			expand_quote(redir->path);
		}
		else
		{
			str_free(&redir->path);
			redir->path = save;
			error_print(save, REDIR_AMBIGUE, NULL, ERROR_EXEC);
		}
	}
}
