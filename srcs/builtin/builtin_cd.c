/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 05:33:26 by rgeny             #+#    #+#             */
/*   Updated: 2022/01/05 14:49:54 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include "env.h"
#include "str.h"
#include "global.h"
#include "error.h"

static int	static_error(char **cmd, t_env *env)
{
	int	len;

	len = str_llen(cmd);
	if (len == 1 && !env_find(env, "HOME"))
	{
		str_printerr("minishell: cd: HOME not set\n", 0, 0, 0);
		return (BUILTIN_ERR_EXEC);
	}
	else if (len > 2)
	{
		str_printerr("minishell: cd: too many arguments\n", 0, 0, 0);
		return (BUILTIN_ERR_EXEC);
	}
	else if (len > 1 && cmd[1][0] == '-'
		&& !cmd[1][1] && !env_find(env, "OLDPWD"))
	{
		str_printerr("minishell: cd: OLDPWD not set\n", 0, 0, 0);
		return (BUILTIN_ERR_EXEC);
	}
	return (SUCCESS);
}

static void	static_replace(t_env *env)
{
	t_env	*tmp;
	char	path[PATH_CHAR_MAX + 1];

	getcwd(path, PATH_CHAR_MAX + 1);
	tmp = env_find(env, "PWD");
	if (tmp)
	{
		env_assign(env, "OLDPWD", str_ndup(tmp->value, str_len(tmp->value, 0)));
		env_assign(env, "PWD", str_ndup(path, str_len(path, 0)));
	}
	else
		env_del_one(env_find(env, "OLDPWD"));
	if (path[0])
		glo_pwd(str_ndup(path, str_len(path, 0)), 1);
}

static int	static_move(char *dir, char *pwd, t_env *env, int b)
{
	char	*path;
	int		ret;

	if (dir && pwd)
		path = str_join(pwd, dir, '/');
	else if (dir)
		path = str_ndup(dir, str_len(dir, 0));
	else if (pwd)
		path = str_ndup(pwd, str_len(pwd, 0));
	else
		return (1);
	ret = chdir(path);
	if (!ret)
		static_replace(env);
	if (!ret && b)
		str_printfd(path, 1);
	free(path);
	return (!!ret);
}

static int	static_env(t_env *env, char *name, char print_path, char *cmd)
{
	t_env	*var;
	char	**split;
	int		i;

	var = env_find(env, name);
	if (print_path < 2)
	{
		if (!var || static_move(0, var->value, env, print_path))
			return (BUILTIN_ERR_EXEC);
		return (SUCCESS);
	}
	if (!var)
		return (SUCCESS);
	split = str_split(var->value, ":");
	i = -1;
	while (split && split[++i])
	{
		if (!static_move(cmd, split[i], env, 1))
		{
			str_free_string(split);
			return (BUILTIN_ERR_EXEC);
		}
	}
	str_free_string(split);
	return (SUCCESS);
}

int	builtin_cd(char **cmd, t_env *env)
{
	if (static_error(cmd, env))
		return (BUILTIN_ERR_EXEC);
	if (!cmd[1])
		return (static_env(env, "HOME", 0, 0));
	if (cmd[1][0] == '-' && !cmd[1][1])
		return (static_env(env, "OLDPWD", 1, 0));
	if (!static_move(cmd[1], 0, env, 0))
		return (SUCCESS);
	if (static_env(env, "CDPATH", 2, cmd[1]))
		return (SUCCESS);
	str_printerr("minishell: cd: ", cmd[1], ": No such file or directory\n", 0);
	return (BUILTIN_ERR_EXEC);
}
