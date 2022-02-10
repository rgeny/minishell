/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_space.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 05:16:45 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/10 11:52:33 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static int	_len_next_word(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != ' ')
	{
		if (s[i] == '"' || s[i] == '\'')
			i += str_clen(&s[i + 1], s[i]) + 2;
		else
			i++;
	}
	return (i);
}

static int	_count_word(char *s)
{
	int	i;
	int	n_space;

	i = 0;
	n_space = 0;
	while (s[i])
	{
		if (s[i] == ' ')
			i += str_first_dif(&s[i], ' ');
		else
		{
			n_space++;
			i += _len_next_word(&s[i]);
		}
	}
	return (n_space);
}

static void	_fill_list(char *s, char **word_list)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == ' ')
			i += str_first_dif(&s[i], ' ');
		else
		{
			len = _len_next_word(&s[i]);
			word_list[j] = str_ndup(&s[i], len);
			j++;
			i += len;
		}
	}
}

static char	**_split_word(char *s)
{
	int		word_n;
	char	**word_list;

	word_n = _count_word(s);
	word_list = uti_calloc(word_n + 1, sizeof(char *));
	if (word_list == NULL)
		return (NULL);
	_fill_list(s, word_list);
	return (word_list);
}

void	expand_space_carg(t_carg *args)
{
	char	**word_list;
	int		i;
	bool	is_first;

	word_list = _split_word(args->content);
	i = 0;
	is_first = true;
	while (word_list[i])
	{
		if (is_first)
		{
			str_free(&args->content);
			args->content = str_dup(word_list[i]);
			is_first = false;
		}
		else
		{
			lst_new_after(args, word_list[i]);
			args = args->next;
		}
		i++;
	}
	str_free_list(&word_list);
}

bool	expand_space_redir(t_redir *redir)
{
	char	**word_list;

	if (_count_word(redir->path) > 1)
		return (false);
	word_list = _split_word(redir->path);
	str_free(&redir->path);
	redir->path = str_dup(word_list[0]);
	str_free_list(&word_list);
	return (true);
}
