/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asterisk_dir_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 11:33:11 by buschiix          #+#    #+#             */
/*   Updated: 2022/02/06 18:57:23 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include "env.h"
#include "str.h"

typedef struct dirent dirent;

static bool	_is_valid_dir(char *dir_name, bool is_hidden)
{
	if (is_hidden == true && dir_name[0] == '.')
		return (true);
	else if (is_hidden == false && dir_name[0] != '.')
		return (true);
	return (false);
}

static int	_size_dir(char *cwd, bool is_hidden)
{
	DIR				*cur_dir;
	struct dirent	*dir;
	int				size;

	cur_dir = opendir(cwd);
	if (cur_dir == NULL)
		return (0);
	size = 0;
	dir = readdir(cur_dir);
	while (dir != NULL)
	{
		if (_is_valid_dir(dir->d_name, is_hidden) == true)
			size++;
		dir = readdir(cur_dir);
	}
	closedir(cur_dir);
	return (size);
}
#include <stdio.h>
static int	_init(DIR **cur_dir, char ***dir_list, bool is_hidden, int *size)
{
	int		len;
	char	cwd[PATH_MAX + 1];

	*cur_dir = NULL;
	*dir_list = NULL;
	if (getcwd(cwd, PATH_MAX + 1) == NULL)
		return (SUCCESS); 
	len = _size_dir(cwd, is_hidden);
	if (len == 0)
		return (SUCCESS);
	*dir_list = uti_calloc(len + 1, sizeof(char *));
	if (*dir_list == NULL)
		return (error_get());
	*cur_dir = opendir(cwd);
	if (*cur_dir == NULL)
		free(*dir_list);
	*size = len;
	return (SUCCESS);
}

char	**asterisk_dir_list(bool is_hidden)
{
	int		len;
	DIR		*cur_dir;
	dirent	*dir;
	char	**dir_list;

	_init(&cur_dir, &dir_list, is_hidden, &len);
	if (cur_dir == NULL || dir_list == NULL || len == 0)
		return (NULL);
	dir = readdir(cur_dir);
	while (len)
	{
		if (_is_valid_dir(dir->d_name, is_hidden) == true)
		{
			len--;
			dir_list[len] = str_dup(dir->d_name);
		}
		dir = readdir(cur_dir);
	}
	closedir(cur_dir);
	return (dir_list);
}
