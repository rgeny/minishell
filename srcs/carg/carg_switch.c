/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carg_switch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 16:03:59 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/10 16:04:18 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "carg.h"

char	**carg_switch_to_list(t_carg *lst, int n_arg)
{
	char	**args;
	int		i;

	args = uti_calloc(n_arg + 1, sizeof(char *));
	if (args == NULL)
		return (NULL);
	i = 0;
	while (i < n_arg)
	{
		args[i] = str_dup(lst->content);
		i++;
		lst = lst->next;
	}
	return (args);
}
