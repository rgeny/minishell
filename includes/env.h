/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 14:27:18 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/06 17:14:06 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H
# include <stdlib.h>
# include <dirent.h>
# include <unistd.h>
# include <stdbool.h>
# include "t_data.h"
# include "str.h"
# include "utils.h"

/*
**	env_init
** Initialize env list with all argument in envp.
** Modify and create if not exist : PWD SHLVL
** Add builtin path in PATH if exist.
*/
void	env_init(t_env **env, char *envp[]);
/*
**	env_new
** Name and value parameter need to be malloc.
** Create a new node and add it to the end of the env list.
** If env var called name exist, then called env_assign and free name parameter.
*/
void	env_new(t_env **env, char *name, char *value);
/*
**	env_find
** return a pointer to env var called name if it exists otherwise return 0.
*/
t_env	*env_find_var(t_env *env, const char *name);
char	*env_find_val(t_env *env, const char *name);
char	*env_find_name(t_env *env, const char *name);
/*
**	env_assign
** new_value parameter need to be malloc.
** assign a new value for env var called name.
** If env var called name doesn't exist, then new_value is free.
*/
void	env_assign(t_env *env, char *name, char *new_value);
/*
**	env_switch
** cpy env in char ** and return this.
*/
char	**env_switch(t_data *data, bool with_not_init); //abc

void	env_del_one(t_env **env, char *name);
void	env_del_all(t_env *env);
#endif
