/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asterisk_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buschiix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 13:35:06 by buschiix          #+#    #+#             */
/*   Updated: 2022/01/18 12:06:38 by buschiix         ###   ########.fr       */
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
	int	l;

	i = 0;
	j = 0;
	k = 0;
	while ((dir[i + j] || word[i + k]) && (word[i + k] == dir[i + j] || word[i + k] == '*'))
	{
		if (word[i + k] == '*')
		{
			while (word[i + k] == '*')
				k++;
			while (word[i + k] != '*' && dir[i + j])
			{
				l = 0;
				while (word[i + k + l] && word[i + k + l] == dir[i + j + l])
					l++;
				if ((!word[i + k + l] && !dir[i + j + l]) || word[i + k + l] == '*')
					i += l;
				else
					j++;
			}
		}
		if (word[i + k] && dir[i + j] && word[i + k] != '*')
			i++;
	}
	if (!word[i + k] && !dir[i + j])
		return (1);
	return (0);
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
			if (new_word)	
				tmp = str_join(new_word, dir_list[i], ' ');
			else
				tmp = str_ndup(dir_list[i], str_len(dir_list[i], 0));
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
			ret = str_ndup(split[i], str_len(split[i], 0));
		i++;
	}
	return (ret);
}

char	*expander_asterisk(char *rl)
{
	char	**dir_list;
	char	**split;
	char	*tmp;
	char	*ret;

	dir_list = asterisk_dir_list();
	split = str_split(rl, " ");
	for (int i = 0; split[i]; i++)
	{
		tmp = _expand(split[i], dir_list);
		if (tmp)
		{
			str_free(split[i]);
			split[i] = tmp;
		}
	}
	str_free_list(dir_list);
	ret = _join(split);
	str_free_list(split);
	return (ret);
}
