/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_assign.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 15:11:41 by rgeny             #+#    #+#             */
/*   Updated: 2022/01/07 23:14:51 by buschiix         ###   ########.fr       */
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
		str_free(new_value);
		return ;
	}
	str_free(node->value);
	node->value = new_value;
}
