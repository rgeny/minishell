/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asterisk_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 13:35:06 by buschiix          #+#    #+#             */
/*   Updated: 2022/01/30 10:16:38 by tokino           ###   ########.fr       */
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

	i = 0;
	while ((dir[i] || word[i]) && (word[i] == dir[i] || word[i] == '*'))
	{
		if (word[i] == '*')
		{
			while (word[i] == '*')
				word++;
			while (word[i] != '*' && dir[i])
			{
				j = 0;
				while (word[i + j] && word[i + j] == dir[i + j])
					j++;
				if ((!word[i + j] && !dir[i + j]) || word[i + j] == '*')
					i += j;
				else
					dir++;
			}
		}
		if (word[i] && dir[i] && word[i] != '*')
			i++;
	}
	return (!word[i] && !dir[i]);
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
		return (0);
	ret = 0;
	if (str_len(rl) == str_clen(rl, '='))
		ret = _expand(rl, dir_list);
	str_free_list(dir_list);
	return (ret);
}
