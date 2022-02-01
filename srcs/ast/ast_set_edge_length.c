/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_set_edge_length.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 19:27:50 by tokino            #+#    #+#             */
/*   Updated: 2022/02/01 21:38:25 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_print.h"

void	_set_left_part(t_ast_printer *p, t_anode *anode)
{
	int i;

	i = 0;
	while (i < anode->height && i < AST_MAX_HEIGHT)
	{
		p->right_profile[i] = INT_MIN;
		i++;
	}
	set_right_profile(p, anode, 0, 0);
}

void	_set_right_part(t_ast_printer *p, t_anode *anode)
{
	int i;

	i = 0;
	while (i < anode->height && i < AST_MAX_HEIGHT)
	{
		p->left_profile[i] = INT_MAX;
		i++;
	}
	set_left_profile(p, anode, 0, 0);
}

void	_set_profiles(t_ast_printer *p, t_anode *anode)
{
	if (anode->left != NULL)
	{
		_set_left_part(p, anode->left);
	}
	if (anode->right != NULL)
	{
		_set_right_part(p, anode->right);
	}
}

int	_get_hmin(t_anode *anode)
{
	if (anode)
		return (anode->lab_height + anode->height);
	else
		return (0);
}

void	compute_edge_lengths(t_ast_printer *p, t_anode *anode)
{
	int	h;
	int	hmin;
	int	i;
	int	delta;

	if (anode == NULL)
		return ;
	compute_edge_lengths(p, anode->left);
	compute_edge_lengths(p, anode->right);
	/* first fill in the edge_length of node */
	if (anode->right == NULL && anode->left == NULL)
		anode->edge_length = 0;
	else
	{
		// hmin = 0;
		_set_profiles(p, anode);
		hmin = uti_min(_get_hmin(anode->left), _get_hmin(anode->right));
		delta = 4;
		i = 0;
		while (i < hmin)
		{
			delta = uti_max(delta, 4 + p->right_profile[i] - p->left_profile[i]);
			i++;
		}
		anode->edge_length = ((delta + 1) / 2) - 1;
	}
	//now fill in the height of node
	h = 1;
	if (anode->left != NULL)
	{
		h = uti_max(anode->left->height + anode->edge_length + anode->left->lab_height, h);
	}
	if (anode->right != NULL)
	{
		h = uti_max(anode->right->height + anode->edge_length + anode->right->lab_height, h);
	}
	anode->height = h;
	printf("%.4s: Tree height = %d, edge_length = %d, command width=%d, command height=%d\n", anode->label[0], anode->height, anode->edge_length, anode->lab_width, anode->lab_height);
}
