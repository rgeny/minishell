/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asterisk_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 13:35:06 by buschiix          #+#    #+#             */
/*   Updated: 2022/02/08 19:13:00 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include <stdbool.h>
#include <stdlib.h>
#include "lst.h"

typedef t_command	t_cmd;

static void	_expand_cmd(t_cmd *cmd, t_carg *args, char *word, char **dir_list)
{
	bool	is_first;

	is_first = true;
	while (*dir_list)
	{
		if (asterisk_cmp(word, *dir_list))
		{
			if (is_first == true)
			{
				args->content = str_dup(*dir_list);
				is_first = false;
			}
			else
			{
				lst_new_after(args, *dir_list);
				args = args->next;
				cmd->arg_nb++;
			}
		}
		dir_list++;
	}
}

static bool	_expand_redir(t_redir *redir, char *word, char **dir_list)
{
	bool	is_first;

	is_first = true;
	while (*dir_list)
	{
		if (asterisk_cmp(word, *dir_list))
		{
			if (is_first == true)
			{
				redir->path = str_dup(*dir_list);
				is_first = false;
			}
			else
			{
				error_print(word, REDIR_AMBIGUE, NULL, 0);
				g_last_return = ERROR_EXEC;
				str_free(redir->path);
				redir->path = str_dup(word);
				return (false);
			}
		}
		dir_list++;
	}
	return (true);
}

bool	expand_asterisk(t_command *cmd, t_carg *args, t_redir *redir)
{
	char	**dir_list;
	bool	is_success;

	is_success = true;
	dir_list = asterisk_dir_list();
	if (dir_list == NULL)
		return (is_success);
	if (args != NULL && str_len(args->content) == str_clen(args->content, '='))
		_expand_cmd(cmd, args, args->content, dir_list);
	if (redir != NULL)
		is_success = _expand_redir(redir, redir->path, dir_list);
	str_free_list(dir_list);
	return (is_success);
}
