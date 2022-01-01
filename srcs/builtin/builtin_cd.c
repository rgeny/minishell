/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 05:33:26 by rgeny             #+#    #+#             */
/*   Updated: 2022/01/01 18:05:01 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include "env.h"
#include "str.h"
#include "global.h"

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
			return (1);
		return (0);
	}
	if (!var)
		return (0);
	split = str_split(var->value, ":");
	i = -1;
	while (split && split[++i])
	{
		if (!static_move(cmd, split[i], env, 1))
		{
			str_free_string(split);
			return (1);
		}
	}
	str_free_string(split);
	return (0);
}

int	builtin_cd(char **cmd, t_env *env)
{
	if (static_error(cmd, env))
		return (1);
	if (!cmd[1])
		return (static_env(env, "HOME", 0, 0));
	if (cmd[1][0] == '-' && !cmd[1][1])
		return (static_env(env, "OLDPWD", 1, 0));
	if (!static_move(cmd[1], 0, env, 0))
		return (0);
	if (static_env(env, "CDPATH", 2, cmd[1]))
		return (0);
	str_printerr("minishell: cd: ", cmd[1], ": No such file or directory\n", 0);
	return (1);
}
