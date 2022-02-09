/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_data.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 13:27:04 by buschiix          #+#    #+#             */
/*   Updated: 2022/02/09 12:33:24 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_DATA_H
# define T_DATA_H
# include "t_env.h"
# include "t_ast.h"
# include "t_lexer.h"

typedef struct s_data
{
	int		pipefd[2];
	int		fd_in;
	t_env	*env;
	t_ast	*ast;
	char	*pwd;
}			t_data;
#endif
