/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 17:27:20 by rgeny             #+#    #+#             */
/*   Updated: 2022/01/01 01:45:45 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H
# include "env.h"

typedef enum e_echo
{
	FLAG_NO,
	FLAG_N
}	t_echo;
typedef enum e_exit
{
	EXIT_MANY_ARG=1,
	EXIT_BAD_ARG
}	t_exit;
typedef enum e_pwd
{
	PWD_DEFAULT=0,
	PWD_BAD_ARG=2
}	t_pwd;
int	builtin_export(char **cmd, t_env **env);
int	builtin_unset(char **cmd, t_env **env);
int	builtin_exit(char **cmd, t_env *env);
#endif
