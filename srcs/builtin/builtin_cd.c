/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 05:33:26 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/04 21:50:37 by buschiix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include "env.h"
#include "str.h"
#include "error.h"
#include "print.h"

static int	_error(char **cmd, t_data *data)
{
	int	len;

	len = str_llen(cmd);
	if (len == 1 && !env_find(data->env, "HOME"))
		return (error_print("cd: ", "HOME not set\n", 0, ERROR_EXEC));
	else if (len > 2)
		return (error_print("cd: ", "too many arguments\n", 0, ERROR_EXEC));
	else if (len > 1 && cmd[1][0] == '-'
		&& !cmd[1][1] && !env_find(data->env, "OLDPWD"))
		return (error_print("cd: ", "OLDPWD not set\n", 0, ERROR_EXEC));
	return (SUCCESS);
}

static void	_replace_pwd_var(t_data *data)
{
	t_env	*tmp;
	char	path[PATH_MAX + 1];

	getcwd(path, PATH_MAX + 1);
	tmp = env_find(data->env, "PWD");
	if (tmp)
	{
		env_assign(data->env, "OLDPWD", str_dup(tmp->value));
		env_assign(data->env, "PWD", str_dup(path));
	}
	else
		env_del_one(env_find(data->env, "OLDPWD"));
	if (path[0])
	{
		str_free(data->pwd);
		data->pwd = str_dup(path);
	}
}

static int	_move(char *dir, char *pwd, t_data *data, int b)
{
	char	*path;
	int		ret;
	char	pathpwd[PATH_MAX + 1];

	path = str_join(pwd, dir, '/');
	if (!path)
		return (ERROR_EXEC);
	ret = chdir(path);
	getcwd(pathpwd, PATH_MAX + 1);
	if (!ret)
		_replace_pwd_var(data);
	if (!ret && b)
		str_print_fd_nl(pathpwd, 1);
	str_free(path);
	return (!!ret);
}

static int	_env(t_data *data, char *name, char print_path, char *cmd)
{
	t_env	*var;
	char	**split;
	int		i;

	var = env_find(data->env, name);
	if (print_path < 2)
	{
		_move(0, var->value, data, print_path);
		return (SUCCESS);
	}
	if (!var)
		return (SUCCESS);
	split = str_split(var->value, ":");
	i = -1;
	while (split && split[++i])
	{
		if (!_move(cmd, split[i], data, 1))
		{
			str_free_list(split);
			return (ERROR_EXEC);
		}
	}
	str_free_list(split);
	return (SUCCESS);
}

int	builtin_cd(char **cmd, t_data *data)
{
	if (_error(cmd, data))
		return (ERROR_EXEC);
	if (!cmd[1])
		return (_env(data, "HOME", 0, 0));
	if (cmd[1][0] == '-' && !cmd[1][1])
		return (_env(data, "OLDPWD", 1, 0));
	if (!_move(cmd[1], 0, data, 0))
		return (SUCCESS);
	if (_env(data, "CDPATH", 2, cmd[1]))
		return (SUCCESS);
	return (error_print("cd: ", cmd[1], ": No such file or directory\n", ERROR_EXEC));
}
