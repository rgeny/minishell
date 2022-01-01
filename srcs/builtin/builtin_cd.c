/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 05:33:26 by rgeny             #+#    #+#             */
/*   Updated: 2022/01/01 08:00:08 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include "env.h"
#include "str.h"

#include <stdio.h>

//int chdir(char *path);
/*
static int	static_move(char *dir, char *pwd)
{
	char	*path;
	int		ret;

	if (!chdir(dir))
		return (0);
	path = str_join(pwd, dir, '/');
	ret = chdir(path) * -1;
	free(path);
	return (ret);
}

static int	static_path(char *dir, t_env *env)
{
	char	**splt;
	int		i;

	if (!env)
		return (1);
	split = str_split(env->value, ":");
	i = 0;
	while (split && split[i])
	{
		if (!static_move(dir, split[i]))
		{
			str_free_string(split);
			return (0);
		}
		i++;
	}
	str_free_string(split);
	return (1);
}

static int	static_error(char **cmd, t_env *env)
{
	int		len;

	len = str_llen(cmd);
	if (len == 1 && !env_find(env, "HOME"))
	{
		str_printerr("minishell: cd: HOME not set\n", 0, 0, 0);
		return (1);
	}
	else if (len == 1)
	{
		static_path(
	}
	return (0);
}

int	builtin_cd(char **cmd, t_env *env)
{
	int		len;
	char	pwd[PATH_CHAR_MAX + 1];

	if (static_error(cmd, env))
		return (1);
	len = str_len(cmd[1], 0);
	if (len && cmd[1][len - 1] == '/')
		cmd[1][len - 1] = 0;
	getcwd(pwd, PATH_CHAR_MAX + 1);
	return (static_move(cmd[1], pwd));
}*/

static int	static_error(char **cmd, t_env *env)
{
	int	len;

	len = str_llen(cmd);
	if (len == 1 && !env_find(env, "HOME"))
	{
		str_printerr("minishell: cd: HOME not set\n", 0, 0, 0);
		return (1);
	}
	else if (len > 2)
	{
		str_printerr("minishell: cd: too many arguments\n", 0, 0, 0);
		return (1);
	}
	else if (len > 1 && cmd[1][0] == '-'
		&& !cmd[1][1] && !env_find(env, "OLDPWD"))
	{
		str_printerr("minishell: cd: OLDPWD not set\n", 0, 0, 0);
		return (1);
	}
	return (0);
}

static int	static_move(char *dir, char *pwd, t_env *env, int b)
{
	char	*path;
	int		ret;
	t_env	*tmp;

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
	{
		tmp = env_find(env, "PWD");
		if (tmp)
		{
			env_assign(env, "OLDPWD", str_ndup(tmp->value, str_len(tmp->value, 0)));
			env_assign(env, "PWD", str_ndup(path, str_len(path, 0)));
		}
		else
			env_del_one(env_find(env, "OLDPWD"));
	}
	if (!ret && b)
		printf("%s\n", path);
	free(path);
	return (!!ret);
}

int	builtin_cd(char **cmd, t_env *env)
{
	t_env	*var;
	char	**split;
	int		i;

	if (static_error(cmd, env))
		return (1);
	if (!cmd[1])
	{
		var = env_find(env, "HOME");
		if (!var || static_move(0, var->value, env, 0))
			return (1);
		return (0);
	}
	if (cmd[1][0] == '-' && !cmd[1][1])
	{
		var = env_find(env, "OLDPWD");
		if (!var || static_move(0, var->value, env, 1))
			return (1);
		return (0);
	}
	if (!static_move(cmd[1], 0, env, 0))
		return (0);
	var = env_find(env, "CDPATH");
	if (var)
	{
		split = str_split(var->value, ":");
		i = 0;
		while (split && split[i])
		{

			if (!static_move(cmd[1], split[i], env, 1))
			{
				str_free_string(split);
				return (0);
			}
			i++;
		}
		str_free_string(split);
	}
	str_printerr("minishell: cd: ", cmd[1], ": No such file or directory\n", 0);
	return (1);
}
