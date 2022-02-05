/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 05:33:26 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/05 14:01:03 by rgeny            ###   ########.fr       */
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

static void	_error(char **cmd, t_data *data)
{
	int	len;

	len = str_llen(cmd);
	if (len == 1 && !env_find_var(data->env, ENV_HOME))
		error_print(CD, ENV_HOME, CD_NOT_SET, ERROR_EXEC);
	else if (len > 2)
		error_print(CD, TOO_MANY_ARGS, NULL, ERROR_EXEC);
	else if (len > 1 && cmd[1][0] == '-' && !cmd[1][1]
		&& !env_find_var(data->env, ENV_OLDPWD))
		error_print(CD, ENV_OLDPWD, CD_NOT_SET, ERROR_EXEC);
}

static int	_replace_pwd_var(t_data *data)
{
	t_env	*tmp;
	char	cwd[PATH_MAX + 1];

	if (getcwd(cwd, PATH_MAX + 1) == NULL)
		return (error_print(CD, GETCWD, NULL, ERROR_EXEC));
	tmp = env_find_var(data->env, ENV_PWD);
	if (tmp)
	{
		env_assign(data->env, ENV_OLDPWD, str_dup(tmp->value));
		env_assign(data->env, ENV_PWD, str_dup(cwd));
	}
	else
		env_del_one(env_find_var(data->env, ENV_OLDPWD));
	if (cwd[0])
	{
		str_free(data->pwd);
		data->pwd = str_dup(cwd);
	}
	return (SUCCESS);
}

static int	_move(char *dir, char *pwd, t_data *data, int print_path)
{
	char	*path;
	char	cwd[PATH_MAX + 1];

	path = str_join(pwd, dir, '/');
	if (!path || chdir(path))
	{
		str_free(path);
		return (ERROR_EXEC);
	}
	getcwd(cwd, PATH_MAX + 1);
	_replace_pwd_var(data);
	if (print_path)
		str_print_fd_nl(cwd, STDOUT_FILENO);
	str_free(path);
	return (SUCCESS);
}

static int	_env(t_data *data, char *name, char print_path, char *cmd)
{
	t_env	*var;
	char	**split;
	int		i;

	var = env_find_var(data->env, name);
	if (print_path < 2)
	{
		_move(NULL, var->value, data, print_path);
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
	if (error_get())
		return (error_get());
	_error(cmd, data);
	if (!error_get() && !cmd[1])
		return (_env(data, ENV_HOME, 0, 0));
	if (!error_get() && cmd[1][0] == '-' && !cmd[1][1])
		return (_env(data, ENV_OLDPWD, 1, 0));
	if (!error_get() && (!_move(cmd[1], 0, data, 0) || _env(data, ENV_CDPATH, 2, cmd[1])))
		return (SUCCESS);
	if (error_get())
		return error_get();
	return (error_print(CD, cmd[1], NO_FILE, ERROR_EXEC));
}
