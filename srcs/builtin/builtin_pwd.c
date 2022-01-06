/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 01:37:12 by rgeny             #+#    #+#             */
/*   Updated: 2022/01/06 23:01:40 by buschiix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "env.h"
#include "str.h"
#include "builtin.h"
#include "error.h"
#include "print.h"
#include "struct.h"

static int	check_arg(char *arg, t_data *data)
{
	if (arg[0] == '-' && arg[1] && arg[1] != '-')
	{
		print_error("pwd: ", arg, ": invalid option\npwd: usage: pwd\n", data);
		return (BUILTIN_ERR_SYNTAX);
	}
	else if (arg[0] == '-' && arg[1] == '-' && arg[2])
	{
		print_error("pwd: --: invalid option\npwd: usage: pwd\n", 0, 0, data);
		return (BUILTIN_ERR_SYNTAX);
	}
	return (SUCCESS);
}

static char	*static_find_pwd(t_env *env)
{
	char	*ret;
	t_env	*pwd;

	pwd = env_find(env, "PWD");
	if (pwd && pwd->value)
	{
		ret = str_ndup(pwd->value, str_len(pwd->value, 0));
		return (ret);
	}
	return (NULL);
}

int	builtin_pwd(char **cmd, t_data *data)
{
	char	tmp[PATH_CHAR_MAX + 1];
	char	*path;

	if (cmd[1] && check_arg(cmd[1], data) == BUILTIN_ERR_SYNTAX)
		return (BUILTIN_ERR_SYNTAX);
	if (!getcwd(tmp, PATH_CHAR_MAX + 1))
		path = static_find_pwd(data->env);
	else
		path = tmp;
	str_printfd(path, 1);
	if (path != tmp)
		free(path);
	return (SUCCESS);
}
