/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_assign.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 15:11:41 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/06 15:41:49 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	env_assign(t_env *env, char *name, char *new_value)
{
	t_env	*node;

	if (new_value == NULL)
		return ;
	node = env_find_var(env, name);
	if (node == NULL)
		return (str_free(new_value));
	str_free(node->value);
	node->value = new_value;
}
