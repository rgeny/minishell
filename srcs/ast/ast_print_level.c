/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_print_level.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 19:30:56 by tokino            #+#    #+#             */
/*   Updated: 2022/02/01 20:08:06 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_print.h"

void	_print_left_edge(t_ast_printer *p, t_anode *anode, int x, int level)
{
	int	i;

	i = 0;
	while (i < (x - p->print_next - (level)))
	{
		printf(" ");
		i++;
	}
	p->print_next += i;
	printf("/");
	p->print_next++;
}

void	_print_right_edge(t_ast_printer *p, t_anode *anode, int x, int level)
{
	int	i;

	i = 0;
	while (i < (x - p->print_next + (level)))
	{
		printf(" ");
		i++;
	}
	p->print_next += i;
	printf("\\");
	p->print_next++;
}

void	_print_label(t_ast_printer *p, t_anode *anode, int x)
{
	int	i;
	int	isleft;

	isleft = (anode->parent_dir == -1);
	i = 0;
	while (i < (x - p->print_next - ((anode->lab_width - isleft) / 2)))
	{
		printf(" ");
		i++;
	}
	p->print_next += i;
	if (anode->line_nb < anode->lab_height)
	{
		printf("%s", anode->label[anode->line_nb]);
		p->print_next += str_len(anode->label[anode->line_nb]);
		anode->line_nb++;
	}
}

void	print_level(t_ast_printer *p, t_anode *anode, int x, int level)
{
	int	i;
	int	isleft;

	if (anode == NULL)
		return ;
	isleft = (anode->parent_dir == -1);
	if (level < anode->lab_height)
		_print_label(p, anode, x);
	else if (anode->edge_length >= level + anode->lab_height - 1)
	{
		if (anode->left != NULL)
			_print_left_edge(p, anode, x, level);
		if (anode->right != NULL)
			_print_right_edge(p, anode, x, level);
	}
	else
	{
		print_level(p, anode->left,
			x - anode->edge_length - 1,
			level - anode->edge_length - 1);
		print_level(p, anode->right,
			x + anode->edge_length + 1,
			level - anode->edge_length - 1);
	}
}
