/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_assign.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 15:11:41 by rgeny             #+#    #+#             */
/*   Updated: 2022/01/07 22:31:55 by buschiix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "str.h"
#include <stdlib.h>

void	env_assign(t_env *env, char *name, char *new_value)
{
	t_env	*node;

	if (!new_value)
		return ;
	node = env_find(env, name);
	if (!node)
	{
		free(new_value);
		return ;
	}
	if (node->value)
		free(node->value);
	node->value = new_value;
}
