/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buschiix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 18:28:18 by buschiix          #+#    #+#             */
/*   Updated: 2022/01/06 18:45:09 by buschiix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_env
{
	struct s_env	*next;
	struct s_env	*prev;
	char			*name;
	char			*value;
}					t_env;
typedef struct s_interactive
{
	unsigned long	line;
	int				is_interactive;
}					t_interactive;
typedef struct s_data
{
	t_env			*env;
	int				ret;
	char			*pwd;
	t_interactive	interactive;
}			t_data;
#endif
