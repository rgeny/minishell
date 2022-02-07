/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asterisk_dir_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 11:33:11 by buschiix          #+#    #+#             */
/*   Updated: 2022/02/07 15:24:34 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <expander.h>

static bool	_is_valid_dir(char *dir_name, bool is_hidden)
{
	if (is_hidden == true && dir_name[0] == '.')
		return (true);
	else if (is_hidden == false && dir_name[0] != '.')
		return (true);
	return (false);
}

static int	_count_dir(char *cwd, bool is_hidden)
{
	DIR				*fd_dir;
	struct dirent	*dir;
	int				n_dir;

	fd_dir = opendir(cwd);
	if (fd_dir == NULL)
		return (0);
	n_dir = 0;
	dir = readdir(fd_dir);
	while (dir != NULL)
	{
		if (_is_valid_dir(dir->d_name, is_hidden) == true)
			n_dir++;
		dir = readdir(fd_dir);
	}
	closedir(fd_dir);
	return (n_dir);
}

static int	_init(DIR **fd_dir, char ***to_return, bool is_hidden, int *n_dir)
{
	char	cwd[PATH_MAX + 1];

	*fd_dir = NULL;
	*to_return = NULL;
	if (getcwd(cwd, PATH_MAX + 1) == NULL)
		return (SUCCESS);
	*n_dir = _count_dir(cwd, is_hidden);
	if (*n_dir == 0)
		return (SUCCESS);
	*to_return = uti_calloc(*n_dir + 1, sizeof(char *));
	if (*to_return == NULL)
		return (error_get());
	*fd_dir = opendir(cwd);
	if (*fd_dir == NULL)
		free(*to_return);
	return (SUCCESS);
}

static void	_fill(DIR *fd_dir, int n_dir, char **to_return, bool is_hidden)
{
	dirent	*cur_dir;

	cur_dir = readdir(fd_dir);
	while (n_dir > 0 && cur_dir != NULL)
	{
		if (_is_valid_dir(cur_dir->d_name, is_hidden) == true)
		{
			n_dir--;
			to_return[n_dir] = str_dup(cur_dir->d_name);
		}
		cur_dir = readdir(fd_dir);
	}
}

char	**asterisk_dir_list(bool is_hidden)
{
	int		n_dir;
	DIR		*fd_dir;
	char	**to_return;

	_init(&fd_dir, &to_return, is_hidden, &n_dir);
	if (fd_dir == NULL || to_return == NULL || n_dir == 0)
		return (NULL);
	_fill(fd_dir, n_dir, to_return, is_hidden);
	closedir(fd_dir);
	uti_quicksort(0, n_dir - 1, to_return);
	return (to_return);
}
