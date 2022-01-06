/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 17:27:20 by rgeny             #+#    #+#             */
/*   Updated: 2022/01/06 22:31:23 by buschiix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H
# include "env.h"

int	builtin_export(char **cmd, t_data *data);
int	builtin_unset(char **cmd, t_data *data);
int	builtin_exit(char **cmd, t_data *data);
int	builtin_cd(char **cmd, t_data *data);
int	builtin_echo(char **cmd);
int	builtin_env(char **envp);
#endif
