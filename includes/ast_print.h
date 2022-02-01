/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_print.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 16:15:30 by tokino            #+#    #+#             */
/*   Updated: 2022/02/01 19:31:25 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_PRINT_H
# define AST_PRINT_H

# include "parser.h"
# include <limits.h>
# include "mem.h"

# define MAX_HEIGHT 1000

typedef struct s_ast_printer {
	int	left_profile[MAX_HEIGHT];
	int	right_profile[MAX_HEIGHT];
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
}	t_anode;

t_anode *build_ascii_tree(t_node *t);
void	set_left_profile(t_ast_printer *p, t_anode *anode, int x, int y);
void	set_right_profile(t_ast_printer *p, t_anode *anode, int x, int y);
void	set_proot_left_profile(t_ast_printer *p, t_anode *anode);
void	compute_edge_lengths(t_ast_printer *p, t_anode *anode);
void	print_level(t_ast_printer *printer, t_anode *node, int x, int level);

#endif