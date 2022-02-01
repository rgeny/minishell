/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_fancy_printer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 19:26:12 by tokino            #+#    #+#             */
/*   Updated: 2022/02/01 21:39:49 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_print.h"

void	free_ascii_tree(t_anode *node)
{
	if (node == NULL)
		return ;
	free_ascii_tree(node->left);
	free_ascii_tree(node->right);
	str_free_list(node->label);
	free(node);
	node = NULL;
}

void	_set_xmin(t_ast_printer *printer, t_anode *proot)
{
	int	i;

	i = 0;
	printer->xmin = 0;
	while (i < proot->height && i < AST_MAX_HEIGHT)
	{
		printer->xmin = uti_min(printer->xmin, printer->left_profile[i]);
		i++;
	}
	printer->xmin = -printer->xmin;
}

// void	_init_printer(t_ast_printer *p)
// {
// 	int i;

// 	i = 0;
// 	while (i < AST_MAX_HEIGHT)
// 	{
// 		p->left_profile[i] = 0;
// 		p->right_profile[i] = 0;
// 		i++;
// 	}
// }

void	print_ast_the_fancy_way(t_node *root)
{
	t_anode			*proot;
	t_ast_printer	printer;
	int				xmin;
	int				i;

	if (root == NULL)
		return ;
	// _init_printer(&printer);
	proot = build_ascii_tree(root);
	compute_edge_lengths(&printer, proot);
	set_proot_left_profile(&printer, proot);
	_set_xmin(&printer, proot);
	printf("xmin = %d\n\n", printer.xmin);
	i = 0;
	while (i < proot->height)
	{
		printer.print_next = 0;
		print_level(&printer, proot, printer.xmin, i);
		printf("\n");
		i++;
	}
	if (proot->height >= AST_MAX_HEIGHT)
	{
		printf("(This tree is taller than %d, and may be drawn incorrectly.)\n", AST_MAX_HEIGHT);
	}
	free_ascii_tree(proot);
}
