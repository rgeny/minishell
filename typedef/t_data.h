/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_data.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buschiix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 13:27:04 by buschiix          #+#    #+#             */
/*   Updated: 2022/02/03 13:34:18 by buschiix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_DATA_H
# define T_DATA_H
# include "t_env.h"
# include "t_ast.h"
# include "t_lexer.h"

typedef struct s_data
{
	t_env			*env;
	t_token			*tokens;
	t_node		*ast_root;
	char			*pwd;
}					t_data;
#endif
