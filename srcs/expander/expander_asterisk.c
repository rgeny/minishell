/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_asterisk.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buschiix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 13:35:06 by buschiix          #+#    #+#             */
/*   Updated: 2022/01/09 17:18:04 by buschiix         ###   ########.fr       */
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
		if (str_cmp(".", dir->d_name) && str_cmp("..", dir->d_name))
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
		if (str_cmp(".", dir->d_name) && str_cmp("..", dir->d_name))
		{
			len--;
			dir_list[len] = str_ndup(dir->d_name, str_len(dir->d_name, 0));
		}
		dir = readdir(cur_dir);
	}
	closedir(cur_dir);
	return (dir_list);
}
/*
char			*getcwd(char *buf, size_t size);
DIR				*opendir(const char *name);
struct dirent	*readdir(DIR *dir);
int				closedir(DIR *dir);

struct dirent
{
	ino_t			d_ino;		numéro d'inoeud
	off_t			d_off;		décalage jusqu'à la dirent suivante
	unsigned short	d_reclen;	longueur de cet enregistrement
	unsigned char	d_type;		type du fichier
	char			d_name[256]	nom du fichier
}
*/

static char	*_expand(char *word, char **dir_list)
{
	int		i;
	char	cp[2];
	char	*new_value;

	i = 0;
	while (dir_list[i])
	{
		if (dir_list[i][0] == word[0])
		{
			cp[0] = word[0];
			cp[1] = 0;
			new_value = str_join(cp, &dir_list[i][1], 0);
			return (new_value);
		}
		i++;
	}
	return (0);
}

char	*expander_asterisk(char *rl)
{
	char	**dir_list;
	char	*tmp;

	dir_list = _dir_list();
	tmp = _expand(rl, dir_list);
	str_free_list(dir_list);
	return (tmp);
}
