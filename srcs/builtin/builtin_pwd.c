/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 01:37:12 by rgeny             #+#    #+#             */
/*   Updated: 2022/01/01 02:03:16 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "env.h"
#include "str.h"
#include "builtin.h"

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

int	main(int argc, char *argv[])
{
	char	path[PATH_CHAR_MAX + 1];

	if (argc > 1)
		check_arg(argv[1]);
	getcwd(path, PATH_CHAR_MAX + 1);
	str_printfd(path, 1);
	write(1, "\n", 1);
	return (PWD_DEFAULT);
}
