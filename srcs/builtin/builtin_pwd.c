/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 01:37:12 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/04 21:56:40 by buschiix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include "env.h"
#include "str.h"
#include "builtin.h"
#include "error.h"
#include "print.h"
#include "struct.h"

static int	check_arg(char *arg)
{
	if (arg[0] == '-' && arg[1] && arg[1] != '-')
		return (error_print("pwd: ", arg, ": invalid option\npwd: usage: pwd\n", ERROR_SYNTAX));
	else if (arg[0] == '-' && arg[1] == '-' && arg[2])
		return (error_print("pwd: --: invalid option\npwd: usage: pwd\n", 0, 0, ERROR_SYNTAX));
	return (SUCCESS);
}

static char	*_find_pwd(t_data *data)
{
	char	*ret;
	t_env	*pwd;

	pwd = env_find(data->env, "PWD");
	if (pwd && pwd->value)
	{
		ret = str_dup(pwd->value);
		return (ret);
	}
	else if (data->pwd)
	{
		ret = str_dup(data->pwd);
		return (ret);
	}
	return (NULL);
}

int	builtin_pwd(char **cmd, t_data *data)
{
	char	tmp[PATH_MAX + 1];
	char	*path;

	if (cmd[1] && check_arg(cmd[1]) == ERROR_SYNTAX)
		return (ERROR_SYNTAX);
	if (!getcwd(tmp, PATH_MAX + 1))
		path = _find_pwd(data);
	else
		path = tmp;
	str_print_fd_nl(path, 1);
	if (path != tmp)
		str_free(path);
	return (SUCCESS);
}
