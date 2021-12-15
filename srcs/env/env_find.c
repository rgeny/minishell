/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_find.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 21:18:35 by rgeny             #+#    #+#             */
/*   Updated: 2021/12/15 14:31:16 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "str.h"

t_env	*env_find(t_env *env, char *s)
{
	while (env && env->prev)
		env = env->prev;
	while (env && str_cmp(env->name, s))
		env = env->next;
	return (env);
}
