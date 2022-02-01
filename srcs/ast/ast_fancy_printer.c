/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_fancy_printer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 19:26:12 by tokino            #+#    #+#             */
/*   Updated: 2022/02/01 19:10:09 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_print.h"

//Free all the nodes of the given tree
void free_ascii_tree(t_anode *node) {
	if (node == NULL)
		return;
	free_ascii_tree(node->left);
	free_ascii_tree(node->right);
	str_free_list(node->label);
	free(node);
	node = NULL;
}

//The following function fills in the lprofile array for the given tree.
//It assumes that the center of the label of the root of this tree
//is located at a position (x,y).  It assumes that the edge_length
//fields have been computed for this tree.
void compute_lprofile(t_ast_printer *printer, t_anode *node, int x, int y) {
	int i, isleft;
	if (node == NULL) return;
	isleft = (node->parent_dir == -1);
	printer->lprofile[y] = uti_min(printer->lprofile[y], x - ((node->lab_width - isleft) / 2));
	if (node->left != NULL) {
		for (i = 1; i <= node->edge_length && y + i < MAX_HEIGHT; i++) {
			printer->lprofile[y + i] = uti_min(printer->lprofile[y + i], x - i);
		}
	}
	compute_lprofile(printer, node->left, x - node->edge_length - 1, y + node->edge_length + 1);
	compute_lprofile(printer, node->right, x + node->edge_length + 1, y + node->edge_length + 1);
}

void compute_rprofile(t_ast_printer *printer, t_anode *node, int x, int y) {
	int i, notleft;
	if (node == NULL) return;
	notleft = (node->parent_dir != -1);
	printer->rprofile[y] = uti_max(printer->rprofile[y], x + ((node->lab_width - notleft) / 2));
	if (node->right != NULL) {
		for (i = 1; i <= node->edge_length && y + i < MAX_HEIGHT; i++) {
			printer->rprofile[y + i] = uti_max(printer->rprofile[y + i], x + i);
		}
	}
	compute_rprofile(printer, node->left, x - node->edge_length - 1, y + node->edge_length + 1);
	compute_rprofile(printer, node->right, x + node->edge_length + 1, y + node->edge_length + 1);
}

//This function fills in the edge_length and
//height fields of the specified tree
void compute_edge_lengths(t_ast_printer *printer, t_anode *node) {
	int h, hmin, i, delta;
	if (node == NULL) return;
	compute_edge_lengths(printer, node->left);
	compute_edge_lengths(printer, node->right);

	/* first fill in the edge_length of node */
	if (node->right == NULL && node->left == NULL)
		node->edge_length = 0;
	 else {
		if (node->left != NULL) {
			for (i = 0; i < node->left->height && i < MAX_HEIGHT; i++) {
				printer->rprofile[i] = INT_MIN;
			}
			compute_rprofile(printer, node->left, 0, 0);
			hmin = node->left->height + node->left->lab_height;
		} else {
			hmin = 0;
		}
		if (node->right != NULL) {
			for (i = 0; i < node->right->height && i < MAX_HEIGHT; i++) {
				printer->lprofile[i] = INT_MAX;
			}
			compute_lprofile(printer, node->right, 0, 0);
			hmin = uti_min(node->right->height + node->right->lab_height, hmin);
		} else {
			hmin = 0;
		}
		delta = 4;
		for (i = 0; i < hmin; i++) {
			delta = uti_max(delta, 4 + printer->rprofile[i] - printer->lprofile[i]);
		}
		node->edge_length = ((delta + 1) / 2) - 1;
	}

	//now fill in the height of node
	h = 1;
	if (node->left != NULL) {
		h = uti_max(node->left->height + node->edge_length + node->left->lab_height, h);
	}
	if (node->right != NULL) {
		h = uti_max(node->right->height + node->edge_length + node->right->lab_height, h);
	}
	node->height = h;
	printf("%.4s: Tree height = %d, edge_length = %d, command width=%d, command height=%d\n", node->label[0], node->height, node->edge_length, node->lab_width, node->lab_height);
}

//This function prints the given level of the given tree, assuming
//that the node has the given x cordinate.
void print_level(t_ast_printer *printer, t_anode *node, int x, int level) {
	int i, isleft;
	if (node == NULL) return;
	isleft = (node->parent_dir == -1);
	if (level < node->lab_height) {
		for (i = 0; i < (x - printer->print_next - ((node->lab_width - isleft) / 2)); i++) {
			printf(" ");
		}
		printer->print_next += i;
		if (node->line_nb < node->lab_height)
		{
			printf("%s", node->label[node->line_nb]);
			printer->print_next += str_len(node->label[node->line_nb]);
			node->line_nb++;
		}
	} else if (node->edge_length >= level + node->lab_height - 1) {
		if (node->left != NULL) {
			for (i = 0; i < (x - printer->print_next - (level)); i++) {
				printf(" ");
			}
			printer->print_next += i;
			printf("/");
			printer->print_next++;
		}
		if (node->right != NULL) {
			for (i = 0; i < (x - printer->print_next + (level)); i++) {
				printf(" ");
			}
			printer->print_next += i;
			printf("\\");
			printer->print_next++;
		}
	} else {
		print_level(printer, node->left,
					x - node->edge_length - 1,
					level - node->edge_length - 1);
		print_level(printer, node->right,
					x + node->edge_length + 1,
					level - node->edge_length - 1);
	}
}

void	print_ast_the_fancy_way(t_node *root)
{
	t_anode *proot;
	t_ast_printer printer;
	int xmin, i;
	
	if (root == NULL)
		return;
	proot = build_ascii_tree(root);
	compute_edge_lengths(&printer, proot);
	for (i = 0; i < proot->height && i < MAX_HEIGHT; i++) {
		printer.lprofile[i] = INT_MAX;
	}
	compute_lprofile(&printer, proot, 0, 0);
	xmin = 0;
	for (i = 0; i < proot->height && i < MAX_HEIGHT; i++) {
		xmin = uti_min(xmin, printer.lprofile[i]);
	}
	printf("xmin = %d\n\n", xmin);
	for (i = 0; i < proot->height; i++) {
		printer.print_next = 0;
		print_level(&printer, proot, -xmin, i);
		printf("\n");
	}
	if (proot->height >= MAX_HEIGHT) {
		printf("(This tree is taller than %d, and may be drawn incorrectly.)\n", MAX_HEIGHT);
	}
	free_ascii_tree(proot);
}
