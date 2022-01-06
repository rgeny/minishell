/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 14:27:18 by rgeny             #+#    #+#             */
/*   Updated: 2022/01/06 16:17:07 by buschiix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H
# define PATH_CHAR_MAX 4096

typedef struct s_env
{
	struct s_env	*next;
	struct s_env	*prev;
	char			*name;
	char			*value;
}				t_env;
typedef struct s_data
{
	t_env	*env;
}			t_data;
/*
**	env_init
** Initialize env list with all argument in envp.
** Modify and create if not exist : PWD SHLVL
** Add builtin path in PATH if exist.
*/
void	env_init(t_env **env, char *envp[], char *exe);
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
t_env	*env_find(t_env *env, char *name);
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
char	**env_switch(t_env **env, int with_not_init); //abc
/*
**	env_new_
** Save the path of the current script in the PATH environment variable.
*/
void	env_new_(char *s, t_env **env);

void	env_del_one(t_env *env);
void	env_del_all(t_env *env);
void	env_print_one(t_env *env);
void	env_print_all(t_env *env);
#endif
