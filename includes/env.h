/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 14:27:18 by rgeny             #+#    #+#             */
/*   Updated: 2021/12/15 12:35:53 by rgeny            ###   ########.fr       */
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

void	env_init(t_env **env, char *envp[]);
t_env	*env_new(char *name, char *value);
void	env_add(t_env **env, t_env *new);

void	env_print_one(t_env *env);
void	env_print_all(t_env *env);

t_env	*env_find(t_env *env, char *s);

void	env_del_all(t_env *env);
void	env_del_one(t_env *env);
#endif
