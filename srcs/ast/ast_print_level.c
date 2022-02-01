/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_print_layer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 19:30:56 by tokino            #+#    #+#             */
/*   Updated: 2022/02/01 19:31:27 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_print.h"

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
