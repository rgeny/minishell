/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 19:22:28 by rgeny             #+#    #+#             */
/*   Updated: 2022/01/18 18:06:26 by buschiix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "env.h"
#include "str.h"

void	env_print_one(t_env *env)
{
	if (env && env->value)
	{
		write(1, env->name, str_len(env->name));
		write(1, "=", 1);
		write(1, env->value, str_len(env->value));
		write(1, "\n", 1);
	}
}

void	env_print_all(t_env *env)
{
	while (env)
	{
		env_print_one(env);
		env = env->next;
	}
}
