/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_interactive.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buschiix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 12:10:22 by buschiix          #+#    #+#             */
/*   Updated: 2022/02/04 20:12:13 by buschiix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_INTERACTIVE_H
# define T_INTERACTIVE_H
# include "file_descriptor.h"

typedef enum e_cmd_interactive
{
	INTERACTIVE_INIT,
	INTERACTIVE_INCR,
	INTERACTIVE_RETURN_IS_IT,
	INTERACTIVE_MOVE_STDERR,
	INTERACTIVE_PRINT_LINE
}	t_cmd_interactive;

typedef struct s_interactive
{
	unsigned long	line;
	int				is_interactive;
}					t_interactive;
#endif
