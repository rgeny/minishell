/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asterisk_dir_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 11:33:11 by buschiix          #+#    #+#             */
/*   Updated: 2022/02/08 14:16:36 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <expander.h>

static int	_count_dir(char *cwd)
{
	DIR			*fd_dir;
	t_dirent	*dir;
	int			n_dir;

	fd_dir = opendir(cwd);
	if (fd_dir == NULL)
		return (0);
	n_dir = 0;
	dir = readdir(fd_dir);
	while (dir != NULL)
	{
		n_dir++;
		dir = readdir(fd_dir);
	}
	closedir(fd_dir);
	return (n_dir);
}

static int	_init(DIR **fd_dir, char ***dir_list, int *n_dir)
{
	char	cwd[PATH_MAX + 1];

	*fd_dir = NULL;
	*dir_list = NULL;
	if (getcwd(cwd, PATH_MAX + 1) == NULL)
		return (ERROR_EXEC);
	*n_dir = _count_dir(cwd);
	if (*n_dir == 0)
		return (ERROR_EXEC);
	*dir_list = uti_calloc(*n_dir + 1, sizeof(char *));
	if (*dir_list == NULL)
		return (error_get());
	*fd_dir = opendir(cwd);
	if (*fd_dir == NULL)
		free(*dir_list);
	return (SUCCESS);
}

static void	_fill(DIR *fd_dir, int n_dir, char **dir_list)
{
	t_dirent	*cur_dir;

	cur_dir = readdir(fd_dir);
	while (n_dir > 0)
	{
		n_dir--;
		dir_list[n_dir] = str_dup(cur_dir->d_name);
		cur_dir = readdir(fd_dir);
	}
}

char	**asterisk_dir_list(void)
{
	int		n_dir;
	DIR		*fd_dir;
	char	**dir_list;

	if (_init(&fd_dir, &dir_list, &n_dir) != SUCCESS)
		return (NULL);
	_fill(fd_dir, n_dir, dir_list);
	closedir(fd_dir);
	uti_quicksort(0, n_dir - 1, dir_list);
	return (dir_list);
}
