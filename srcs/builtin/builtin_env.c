/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 15:23:28 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/10 11:44:17 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_env(char **envp)
{
	int	i;

	if (envp == NULL)
		return (SUCCESS);
	i = 0;
	while (envp[i] != NULL)
	{
		str_print_fd_nl(envp[i], STDOUT_FILENO);
		i++;
	}
	str_free_list(&envp);
	return (SUCCESS);
}
