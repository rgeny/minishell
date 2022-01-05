/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 17:27:20 by rgeny             #+#    #+#             */
/*   Updated: 2022/01/05 14:59:20 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H
# include "env.h"

int	builtin_export(char **cmd, t_env **env);
int	builtin_unset(char **cmd, t_env **env);
int	builtin_exit(char **cmd, t_env *env);
int	builtin_cd(char **cmd, t_env *env);
#endif
