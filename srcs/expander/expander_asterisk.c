/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_asterisk.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buschiix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 13:35:06 by buschiix          #+#    #+#             */
/*   Updated: 2022/01/14 04:19:48 by buschiix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include "env.h"
#include "str.h"

#include <stdio.h>

static int	_size_dir(void)
{
	char			buf[PATH_CHAR_MAX + 1];
	DIR				*cur_dir;
	struct dirent	*dir;
	int				i;

	getcwd(buf, PATH_CHAR_MAX + 1);
	cur_dir = opendir(buf);
	i = 0;
	dir = readdir(cur_dir);
	while (dir)
	{
		if (dir->d_name[0] != '.')
			i++;
		dir = readdir(cur_dir);
	}
	closedir(cur_dir);
	return (i);
}

static char	**_dir_list(void)
{
	int				len;
	char			buf[PATH_CHAR_MAX + 1];
	DIR				*cur_dir;
	struct dirent	*dir;
	char			**dir_list;

	len = _size_dir();
	getcwd(buf, PATH_CHAR_MAX + 1);
	cur_dir = opendir(buf);
	dir = readdir(cur_dir);
	dir_list = malloc(sizeof(char *) * (len + 1));
	dir_list[len] = 0;
	while (len)
	{
		if (dir->d_name[0] != '.')
		{
			len--;
			dir_list[len] = str_ndup(dir->d_name, str_len(dir->d_name, 0));
		}
		dir = readdir(cur_dir);
	}
	closedir(cur_dir);
	return (dir_list);
}

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

char	*expander_asterisk(char *rl)
{
	char	**dir_list;
	char	**split;
	char	*tmp;
	char	*tmp2;

	dir_list = _dir_list();
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
	tmp = 0;
	tmp2 = 0;
	for (int i = 0; split[i]; i++)
	{
		if (tmp)
		{
			tmp2 = str_join(tmp, split[i], ' ');
			free(tmp);
			tmp = tmp2;
		}
		else
		{
			tmp = str_ndup(split[i], str_len(split[i], 0));
		}
	}
	str_free_list(dir_list);
	str_free_list(split);
	return (tmp);
}
