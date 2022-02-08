/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asterisk_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 13:35:06 by buschiix          #+#    #+#             */
/*   Updated: 2022/02/08 11:48:44 by buschiix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include <stdbool.h>
#include <stdlib.h>
#include "lst.h"

static bool	_change_values(int *j, char **p, int i, int n_quote)
{
	*j += i;
	*p += n_quote;
	return (true);
}

static bool	_is_valid_name(char *word, char *dir, char **p, int *j)
{
	int		i;
	int		n_quote;
	int		len;

	i = 0;
	n_quote = 0;
	while (word[i + n_quote] != '\0' && word[i + n_quote] != '*')
	{
		if (uti_is_in_charset(word[i + n_quote], QUOTES))
		{
			len = str_clen(&word[i + n_quote + 1], word[i + n_quote]);
			if (str_ncmp(&word[i + n_quote + 1], &dir[i], len) != 0)
				return (false);
			i += len;
			n_quote += 2;
		}
		else if (word[i + n_quote] != dir[i])
			return (false);
		else
			i++;
	}
	if (word[i + n_quote] == '*'
		|| (word[i + n_quote] == '\0' && dir[i] == '\0'))
		return (_change_values(j, p, i, n_quote));
	return (false);
}

static int	_cmp(char *word, char *dir)
{
	int		i;
	int		quote;
	bool	asterisk;

	i = 0;
	asterisk = false;
	while (word[i] != '\0' || dir[i] != '\0')
	{
		if (word[i] == '*')
		{
			word += str_first_dif(&word[i], '*');
			asterisk = true;
		}
		else if (asterisk == true)
		{
			while (dir[i] && _is_valid_name(&word[i], &dir[i], &word, &i) == 0)
				dir++;
			asterisk = false;
		}
		else if (_is_valid_name(&word[i], &dir[i], &word, &i) == 0)
			return (0);
	}
	return (word[i] == '\0' && dir[i] == '\0');
}

/*static char	*_expand(char *word, char **dir_list)
{
	int		i;
	char	*new_word;
	char	*tmp;

	new_word = 0;
	i = 0;
	while (dir_list[i])
	{
		if (_cmp(word, dir_list[i]))
		{
			tmp = str_join(new_word, dir_list[i], ' ');
			str_free(new_word);
			new_word = tmp;
		}
		i++;
	}
	return (new_word);
}

char	*expander_asterisk(char *word)
{
	char	**dir_list;
	char	*new_word;

	dir_list = asterisk_dir_list(word[0] == '.');
	if (dir_list == NULL)
		return (NULL);
	new_word = NULL;
	if (str_len(word) == str_clen(word, '='))
		new_word = _expand(word, dir_list);
	str_free_list(dir_list);
	return (new_word);
}*/

static void	_expand_cmd(t_command *cmd, t_carg **args, char **dir_list)
{
	bool	is_first;
	char	*word;

	is_first = true;
	word = (*args)->content;
	while (*dir_list)
	{
		if (_cmp(word, *dir_list))
		{
			if (is_first == true)
			{
				(*args)->content = str_dup(*dir_list);
				is_first = false;
			}
			else
			{
				lst_new_after(*args, *dir_list);
				*args = (*args)->next;
				cmd->arg_nb++;
			}
		}
		dir_list++;
	}
	if ((*args)->content != word)
		str_free(word);
}

static bool	_expand_redir(t_redir *redir, char **dir_list)
{
	bool	is_first;
	char	*word;

	is_first = true;
	word = redir->path;
	while (*dir_list)
	{
		if (_cmp(word, *dir_list))
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
				redir->path = word;
				return (false);
			}
		}
		dir_list++;
	}
	if (redir->path != word)
		str_free(word);
	return (true);
}

bool	_expand_asterisk(t_command *cmd)
{
	t_carg	*args;
	t_redir	*redir;
	char	**dir_list;

	args = cmd->cargs;
	redir = cmd->redirections;
	while (args)
	{
		dir_list = asterisk_dir_list(args->content[0] == '.');
		if (dir_list != NULL)
		{
			if (str_len(args->content) == str_clen(args->content, '='))
				_expand_cmd(cmd, &args, dir_list);
			str_free_list(dir_list);
		}
		args = args->next;
	}
	int	i = 0;
	while (i < cmd->redir_nb)
	{
		dir_list = asterisk_dir_list(redir[i].path[0] == '.');
		if (dir_list != NULL)
		{
			if (_expand_redir(&redir[i], dir_list) == false)
			{
				str_free_list(dir_list);
				return (false);
			}
			str_free_list(dir_list);
		}
		i++;
	}
	return (true);
}
