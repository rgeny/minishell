/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_set_profiles.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 18:28:23 by tokino            #+#    #+#             */
/*   Updated: 2022/02/01 21:19:10 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_print.h"

void	set_left_profile(t_ast_printer *p, t_anode *anode, int x, int y)
{
	int	i;
	int	isleft;

	if (anode == NULL)
		return ;
	isleft = (anode->parent_dir == -1);
	p->left_profile[y] = \
		uti_min(p->left_profile[y], x - ((anode->lab_width - isleft) / 2));
	if (anode->left != NULL)
	{
		i = 1;
		while (i <= anode->edge_length && y + i < AST_MAX_HEIGHT)
		{
			p->left_profile[y + i] = uti_min(p->left_profile[y + i], x - i);
			i++;
		}
	}
	set_left_profile(p, anode->left, \
		x - anode->edge_length - 1, \
		y + anode->edge_length + 1);
	set_left_profile(p, anode->right, \
		x + anode->edge_length + 1, \
		y + anode->edge_length + 1);
}

void	set_right_profile(t_ast_printer *p, t_anode *anode, int x, int y)
{
	int	i;
	int	notleft;

	if (anode == NULL)
		return ;
	notleft = (anode->parent_dir != -1);
	p->right_profile[y] = \
		uti_max(p->right_profile[y], x + ((anode->lab_width - notleft) / 2));
	if (anode->right != NULL)
	{
		i = 1;
		while (i <= anode->edge_length && y + i < AST_MAX_HEIGHT)
		{
			p->right_profile[y + i] = uti_max(p->right_profile[y + i], x + i);
			i++;
		}
	}
	set_right_profile(p, anode->left, \
		x - anode->edge_length - 1, \
		y + anode->edge_length + 1);
	set_right_profile(p, anode->right, \
		x + anode->edge_length + 1, \
		y + anode->edge_length + 1);
}

void	set_proot_left_profile(t_ast_printer *p, t_anode *anode)
{
	int	i;

	i = 0;
	while (i < anode->height && i < AST_MAX_HEIGHT)
	{
		p->left_profile[i] = INT_MAX;
		i++;
	}
	set_left_profile(p, anode, 0, 0);
}
