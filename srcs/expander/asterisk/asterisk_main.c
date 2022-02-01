/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asterisk_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 13:35:06 by buschiix          #+#    #+#             */
/*   Updated: 2022/02/01 15:51:54 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include "env.h"
#include "str.h"
#include "expander.h"

static int	_cmp(char *word, char *dir)
{
	int	i;
	int	j;
	int	k;
	int	b;

	i = 0;
	k = 0;
	b = 0;
	while (word[i + k]
		&& (word[i + k] == dir[i] || word[i + k] == '*'
			|| (!b && (word[i + k] == '\'' || word[i + k] == '\"'))
			|| word[i + k] == b))
	{
		if (word[i + k] == '*' && !b)
		{
			while (word[i + k] == '*')
				word++;
			while (word[i + k] != '*' && dir[i])
			{
				j = 0;
				while (word[i + j + k] && word[i + j + k] == dir[i + j])
					j++;
				if ((!word[i + j + k] && !dir[i + j]) || word[i + j + k] == '*')
					i += j;
				else
					dir++;
			}
		}
		if (word[i + k] && dir[i] && (word[i + k] != '*' || b))
		{
			if (!b && (word[i + k] == '\'' || word[i + k] == '\"'))
			{
				b = word[i + k];
				k++;
			}
			else if (word[i + k] == b)
			{
				b = 0;
				k++;
			}
			else
				i++;
		}
	}
	return (!word[i + k] && !dir[i]);
}

static char	*_expand(char *word, char **dir_list)
{
	int		i;
	char	*new_word;
	char	*tmp;

	new_word = 0;
	tmp = 0;
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

static char	*_join(char **split)
{
	int		i;
	char	*tmp;
	char	*ret;

	i = 0;
	ret = 0;
	while (split[i])
	{
		if (ret)
		{
			tmp = str_join(ret, split[i], ' ');
			str_free(ret);
			ret = tmp;
		}
		else
			ret = str_dup(split[i]);
		i++;
	}
	return (ret);
}

char	*expander_asterisk(char *rl)
{
	char	**dir_list;
	char	*ret;

	dir_list = asterisk_dir_list(rl[0] == '.');
	if (!dir_list)
		return (NULL);
	ret = 0;
	if (str_len(rl) == str_clen(rl, '='))
		ret = _expand(rl, dir_list);
	str_free_list(dir_list);
	return (ret);
}
