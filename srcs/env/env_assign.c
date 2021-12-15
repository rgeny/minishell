/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_assign.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 15:11:41 by rgeny             #+#    #+#             */
/*   Updated: 2021/12/15 17:00:00 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <stdlib.h>

void	env_assign(t_env *env, char *name, char *new_value)
{
	t_env	*node;

	node = env_find(env, name);
	if (!node)
		return ;
	free(node->value);
	node->value = new_value;
}
