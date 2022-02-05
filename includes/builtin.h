/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 17:27:20 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/05 16:10:00 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H
# include <dirent.h>
# include <unistd.h>
# include <stdbool.h>
# include "env.h"
# include "str.h"
# include "error.h"
# include "t_data.h"

int	builtin_export(char **cmd, t_data *data);
int	builtin_unset(char **cmd, t_data *data);
int	builtin_exit(char **cmd, t_data *data);
int	builtin_cd(char **cmd, t_data *data);
int	builtin_echo(char **cmd);
int	builtin_env(char **envp);
int	builtin_pwd(char **cmd, t_data *data);
#endif
