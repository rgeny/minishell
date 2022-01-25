/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asterisk_dir_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 11:33:11 by buschiix          #+#    #+#             */
/*   Updated: 2022/01/25 11:41:25 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include "env.h"
#include "str.h"

static int	_size_dir(char *buf)
{
	DIR				*cur_dir;
	struct dirent	*dir;
	int				i;

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

char	**asterisk_dir_list(void)
{
	int				len;
	char			buf[PATH_MAX + 1];
	DIR				*cur_dir;
	struct dirent	*dir;
	char			**dir_list;

	getcwd(buf, PATH_MAX + 1);
	len = _size_dir(buf);
	cur_dir = opendir(buf);
	dir = readdir(cur_dir);
	dir_list = malloc(sizeof(char *) * (len + 1));
	dir_list[len] = 0;
	while (len)
	{
		if (dir->d_name[0] != '.')
		{
			len--;
			dir_list[len] = str_dup(dir->d_name);
		}
		dir = readdir(cur_dir);
	}
	closedir(cur_dir);
	return (dir_list);
}
