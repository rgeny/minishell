/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_fancy_printer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 19:26:12 by tokino            #+#    #+#             */
/*   Updated: 2022/02/05 15:56:13 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_print.h"

static void	_free_ascii_tree(t_anode *node)
{
	if (node == NULL)
		return ;
	_free_ascii_tree(node->left);
	_free_ascii_tree(node->right);
	str_free_list(node->label);
	free(node);
	node = NULL;
}

static void	_set_xmin(t_ast_printer *printer, t_anode *proot)
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

static void	_init_printer(t_ast_printer *p)
{
	int	i;

	i = 0;
	while (i < AST_MAX_HEIGHT)
	{
		p->left_profile[i] = 0;
		p->right_profile[i] = 0;
		i++;
	}
}

void	print_ast_the_fancy_way(t_node *root)
{
	t_anode			*proot;
	t_ast_printer	printer;
//	int				xmin;
	int				i;

	if (root == NULL)
		return ;
	printf("\nWhat a wonderfull AST :\n");
	_init_printer(&printer);
	proot = build_ascii_tree(root);
	compute_edge_lengths(&printer, proot);
	set_proot_left_profile(&printer, proot);
	_set_xmin(&printer, proot);
	i = 0;
	while (i < proot->height)
	{
		printer.print_next = 0;
		print_level(&printer, proot, printer.xmin, i);
		printf("\n");
		i++;
	}
	_free_ascii_tree(proot);
}
