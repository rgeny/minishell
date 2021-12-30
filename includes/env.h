/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 14:27:18 by rgeny             #+#    #+#             */
/*   Updated: 2021/12/30 20:26:24 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

typedef struct s_env
{
	struct s_env	*next;
	struct s_env	*prev;
	char			*name;
	char			*value;
}				t_env;

/*
**	env_init
** Initialize env list with all argument in envp.
*/
void	env_init(t_env **env, char *envp[], char *cmd);
/*
**	env_new
** Create a new node and add it to the end of the env list.
*/
void	env_new(t_env **env, char *name, char *value);

void	env_print_one(t_env *env);
void	env_print_all(t_env *env);

t_env	*env_find(t_env *env, char *name);

void	env_assign_force(t_env *env, char *name, char *new_value);
void	env_assign(t_env *env, char *name, char *new_value);

char	**env_switch(t_env *env, int with_not_init);

void	env_del_all(t_env *env);
void	env_del_one(t_env *env);

int		env_export(char **cmd, t_env **env);
int		env_unset(char **cmd, t_env *env);
#endif
