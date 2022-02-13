/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 01:37:12 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/13 10:32:33 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	_check_arg(char *arg)
{
	if (arg[0] == '-' && arg[1] != '\0' && arg[1] != '-')
		return (error_print(PWD, arg, BAD_OPT, ERROR_SYNTAX));
	else if (arg[0] == '-' && arg[1] == '-' && arg[2] != '\0')
		return (error_print(PWD, DOUBLE_HYPHEN, BAD_OPT, ERROR_SYNTAX));
	return (SUCCESS);
}

static char	*_find_pwd(t_data *data)
{
	t_env	*pwd;

	pwd = env_find_var(data->env, "PWD");
	if (pwd && pwd->value)
		return (str_dup(pwd->value));
	else
		return (str_dup(data->pwd));
}

int	builtin_pwd(char **cmd, t_data *data)
{
	char	*path;

	if (cmd[0] != NULL && _check_arg(cmd[0]) != SUCCESS)
		return (error_get());
	path = getcwd(NULL, 0);
	if (path == NULL)
		path = _find_pwd(data);
	str_print_fd_nl(path, data->pipefd[1]);
	str_free(&path);
	return (SUCCESS);
}
