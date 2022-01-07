/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 15:23:28 by rgeny             #+#    #+#             */
/*   Updated: 2022/01/07 23:12:45 by buschiix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "error.h"
#include "str.h"

int	builtin_env(char **envp)
{
	int	i;

	if (envp)
	{
		i = 0;
		while (envp[i])
		{
			write(1, envp[i], str_len(envp[i], 0));
			write(1, "\n", 1);
			i++;
		}
		str_free_list(envp);
	}
	return (SUCCESS);
}
