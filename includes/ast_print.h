/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_print.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 16:15:30 by tokino            #+#    #+#             */
/*   Updated: 2022/02/01 16:18:52 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_PRINT_H
# define AST_PRINT_H

# include "parser.h"
# include <limits.h>
# include "mem.h"

# define MAX_HEIGHT 1000

typedef struct s_ast_printer {
	int	lprofile[MAX_HEIGHT];
	int	rprofile[MAX_HEIGHT];
	int	print_next;
}	t_ast_printer;

typedef struct s_asciinode {
	struct s_asciinode	*left;
	struct s_asciinode	*right;
	int					edge_length;
	int					height;
	int					parent_dir; //-1=left, 0=root, 1=right
	char				**label;
	int					lab_width;
	int					lab_height;
	int					line_nb;
}	t_asciinode;

#endif
