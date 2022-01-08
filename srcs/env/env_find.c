/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_find.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 21:18:35 by rgeny             #+#    #+#             */
/*   Updated: 2022/01/08 20:23:56 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "str.h"

t_env	*env_find(t_env *env, char *name)
{
	int	len;

	len = str_len_alnum(name);
	while (env && env->prev)
		env = env->prev;
	while (env && str_cmp(env->name, name))
		env = env->next;
	return (env);
}
