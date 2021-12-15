/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 19:22:28 by rgeny             #+#    #+#             */
/*   Updated: 2021/12/15 14:33:35 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "env.h"
#include "str.h"

void	env_print_one(t_env *env)
{
	if (env)
	{
		write(1, env->name, str_len(env->name, 0));
		write(1, "=", 1);
		write(1, env->value, str_len(env->value, 0));
	}
	write(1, "\n", 1);
}

void	env_print_all(t_env *env)
{
	while (env)
	{
		env_print_one(env);
		env = env->next;
	}
}
