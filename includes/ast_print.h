/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_print.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 16:15:30 by tokino            #+#    #+#             */
/*   Updated: 2022/02/11 14:55:06 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_PRINT_H
# define AST_PRINT_H

# include <limits.h>
# include "mem.h"
# include "parser.h"
# include "common.h"

# define AST_MAX_HEIGHT 1000

typedef struct s_ast_printer {
	int	left_profile[AST_MAX_HEIGHT];
	int	right_profile[AST_MAX_HEIGHT];
	int	print_next;
	int	xmin;
}	t_ast_printer;

typedef struct s_asciinode {
	struct s_asciinode	*left;
	struct s_asciinode	*right;
	int					edge_length;
	int					height;
	int					parent_dir;
	char				**label;
	int					lab_width;
	int					lab_height;
	int					line_nb;
}	t_anode;

t_anode	*build_ascii_tree(t_ast *t);
void	set_label(t_anode *anode, t_ast *tnode);
void	set_left_profile(t_ast_printer *p, t_anode *anode, int x, int y);
void	set_right_profile(t_ast_printer *p, t_anode *anode, int x, int y);
void	set_proot_left_profile(t_ast_printer *p, t_anode *anode);
void	compute_edge_lengths(t_ast_printer *p, t_anode *anode);
void	print_level(t_ast_printer *printer, t_anode *node, int x, int level);

#endif
