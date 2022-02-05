/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 05:33:26 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/05 21:34:18 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	_check_error(char **cmd, t_data *data)
{
	int	len;

	len = str_llen(cmd);
	if (len == 0 && env_find_var(data->env, ENV_HOME) == NULL)
		return (error_print(CD, ENV_HOME, CD_NOT_SET, ERROR_EXEC));
	else if (len > 1)
		return (error_print(CD, TOO_MANY_ARGS, NULL, ERROR_EXEC));
	else if (len > 0 && cmd[0][0] == '-' && cmd[0][1] == '\0'
		&& env_find_var(data->env, ENV_OLDPWD) == NULL)
		return (error_print(CD, ENV_OLDPWD, CD_NOT_SET, ERROR_EXEC));
	return (SUCCESS);
}

static int	_replace_pwd(t_data *data, char *cwd)
{
	t_env	*tmp;

	tmp = env_find_var(data->env, ENV_PWD);
	if (tmp != NULL)
	{
		env_assign(data->env, ENV_OLDPWD, str_dup(tmp->value));
		env_assign(data->env, ENV_PWD, str_dup(cwd));
	}
	else
		env_del_one(env_find_var(data->env, ENV_OLDPWD));
	str_free(data->pwd);
	data->pwd = str_dup(cwd);
	return (SUCCESS);
}

static int	_move_cwd(char *dir, char *pwd, t_data *data, bool print_path)
{
	char	*path;
	char	cwd[PATH_MAX + 1];
	int		ret;

	path = str_join(pwd, dir, '/');
	ret = chdir(path);
	str_free(path);
	if (ret != 0 && dir != NULL)
		return (ERROR_EXEC);
	if (getcwd(cwd, PATH_MAX + 1) == NULL)
		return (error_print(CD, GETCWD, NULL, ERROR_EXEC));
	if (print_path == true)
		str_print_fd_nl(cwd, STDOUT_FILENO);
	return (_replace_pwd(data, cwd));
}

static int	_move_with_cdpath(t_data *data, char *cmd)
{
	char	**split;
	int		i;
	char	*cdpath;

	cdpath = env_find_val(data->env, ENV_CDPATH);
	split = str_split(cdpath, ":");
	if (split == NULL)
		return (ERROR_EXEC);
	i = 0;
	while (split[i] != NULL && _move_cwd(cmd, split[i], data, true) != SUCCESS)
		i++;
	if (split[i] == NULL)
		error_print(NULL, NULL, NULL, ERROR_EXEC);
	str_free_list(split);
	return (error_get());
}

int	builtin_cd(char **cmd, t_data *data)
{
	if (_check_error(cmd, data) != SUCCESS)
		return (error_get());
	if (cmd[0] == NULL)
		return (_move_cwd(NULL, env_find_val(data->env, ENV_HOME), data, 0));
	if (cmd[0][0] == '-' && cmd[0][1] == '\0')
		return (_move_cwd(NULL, env_find_val(data->env, ENV_OLDPWD), data, 1));
	if (_move_cwd(cmd[0], 0, data, 0) == SUCCESS
		|| _move_with_cdpath(data, cmd[0]) == SUCCESS)
		return (SUCCESS);
	if (error_get() != SUCCESS)
		return (error_get());
	return (error_print(CD, cmd[0], NO_FILE, ERROR_EXEC));
}
