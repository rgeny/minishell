/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_set_edge_length.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 19:27:50 by tokino            #+#    #+#             */
/*   Updated: 2022/02/01 19:28:52 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_print.h"

//This function fills in the edge_length and
//height fields of the specified tree
void compute_edge_lengths(t_ast_printer *p, t_anode *anode) {
	int h, hmin, i, delta;
	if (anode == NULL) return;
	compute_edge_lengths(p, anode->left);
	compute_edge_lengths(p, anode->right);

	/* first fill in the edge_length of node */
	if (anode->right == NULL && anode->left == NULL)
		anode->edge_length = 0;
	 else {
		if (anode->left != NULL) {
			for (i = 0; i < anode->left->height && i < MAX_HEIGHT; i++) {
				p->right_profile[i] = INT_MIN;
			}
			set_right_profile(p, anode->left, 0, 0);
			hmin = anode->left->height + anode->left->lab_height;
		} else {
			hmin = 0;
		}
		if (anode->right != NULL) {
			for (i = 0; i < anode->right->height && i < MAX_HEIGHT; i++) {
				p->left_profile[i] = INT_MAX;
			}
			set_left_profile(p, anode->right, 0, 0);
			hmin = uti_min(anode->right->height + anode->right->lab_height, hmin);
		} else {
			hmin = 0;
		}
		delta = 4;
		for (i = 0; i < hmin; i++) {
			delta = uti_max(delta, 4 + p->right_profile[i] - p->left_profile[i]);
		}
		anode->edge_length = ((delta + 1) / 2) - 1;
	}

	//now fill in the height of node
	h = 1;
	if (anode->left != NULL) {
		h = uti_max(anode->left->height + anode->edge_length + anode->left->lab_height, h);
	}
	if (anode->right != NULL) {
		h = uti_max(anode->right->height + anode->edge_length + anode->right->lab_height, h);
	}
	anode->height = h;
	printf("%.4s: Tree height = %d, edge_length = %d, command width=%d, command height=%d\n", anode->label[0], anode->height, anode->edge_length, anode->lab_width, anode->lab_height);
}
