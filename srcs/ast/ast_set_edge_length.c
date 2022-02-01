/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_set_edge_length.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 19:27:50 by tokino            #+#    #+#             */
/*   Updated: 2022/02/01 22:01:25 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_print.h"

static void	_set_profiles(t_ast_printer *p, t_anode *anode)
{
	int	i;

	if (anode->left != NULL)
	{
		i = 0;
		while (i < anode->left->height && i < AST_MAX_HEIGHT)
		{
			p->right_profile[i] = INT_MIN;
			i++;
		}
		set_right_profile(p, anode->left, 0, 0);
	}
	if (anode->right != NULL)
	{
		i = 0;
		while (i < anode->right->height && i < AST_MAX_HEIGHT)
		{
			p->left_profile[i] = INT_MAX;
			i++;
		}
		set_left_profile(p, anode->right, 0, 0);
	}
}

static int	_get_hmin(t_anode *anode)
{
	if (anode)
		return (anode->lab_height + anode->height);
	else
		return (0);
}

static void	_set_height(t_anode *anode)
{
	int		h;
	t_anode	*child;

	h = 1;
	if (anode->left != NULL)
	{
		child = anode->left;
		h = uti_max(child->height + anode->edge_length + child->lab_height, h);
	}
	if (anode->right != NULL)
	{
		child = anode->right;
		h = uti_max(child->height + anode->edge_length + child->lab_height, h);
	}
	anode->height = h;
}

void	compute_edge_lengths(t_ast_printer *p, t_anode *anode)
{
	int	hmin;
	int	i;
	int	delt;

	if (anode == NULL)
		return ;
	compute_edge_lengths(p, anode->left);
	compute_edge_lengths(p, anode->right);
	if (anode->right == NULL && anode->left == NULL)
		anode->edge_length = 0;
	else
	{
		_set_profiles(p, anode);
		hmin = uti_min(_get_hmin(anode->left), _get_hmin(anode->right));
		delt = 4;
		i = 0;
		while (i < hmin)
		{
			delt = uti_max(delt, 4 + p->right_profile[i] - p->left_profile[i]);
			i++;
		}
		anode->edge_length = ((delt + 1) / 2) - 1;
	}
	_set_height(anode);
}
