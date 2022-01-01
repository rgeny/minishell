/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 01:37:12 by rgeny             #+#    #+#             */
/*   Updated: 2022/01/01 18:09:54 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "env.h"
#include "str.h"
#include "builtin.h"
#include "global.h"

static void	check_arg(char *arg)
{
	if (arg[0] == '-' && arg[1] && arg[1] != '-')
	{
		str_printerr("minishell: pwd: ", arg,
			": invalid option\npwd: usage: pwd\n", 0);
		exit(2);
	}
	else if (arg[0] == '-' && arg[1] == '-' && arg[2])
	{
		str_printerr("minishell: pwd: --: invalid option\n",
			"pwd: usage: pwd\n", 0, 0);
		exit(2);
	}
}

static char	*static_find_pwd(char *envp[])
{
	int		i;
	char	**split;
	char	*ret;

	i = 0;
	while (envp[i])
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'W'
			&& envp[i][2] == 'D' && envp[i][3] == '=')
			break ;
		i++;
	}
	if (envp[i])
	{
		split = str_split(envp[i], "=");
		ret = str_ndup(split[1], str_len(split[1], 0));
		str_free_string(split);
		return (ret);
	}
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	tmp[PATH_CHAR_MAX + 1];
	char	*path;

	if (argc > 1)
		check_arg(argv[1]);
	if (!getcwd(tmp, PATH_CHAR_MAX + 1))
		path = static_find_pwd(envp);
	else
		path = tmp;
	str_printfd(path, 1);
	if (path != tmp)
		free(path);
	return (PWD_DEFAULT);
}
