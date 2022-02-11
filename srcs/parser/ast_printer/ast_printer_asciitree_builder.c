/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_printer_asciitree_builder.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 16:39:54 by tokino            #+#    #+#             */
/*   Updated: 2022/02/11 14:53:41 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_print.h"

static char	*_set_sep_label(t_ast *tnode)
{
	if (tnode->type == E_NODE_TYPE_PIPE)
	{
		if (tnode->is_subshell)
			return (str_dup("(s)PIPE"));
		else
			return (str_dup("PIPE"));
	}
	else if (tnode->type == E_NODE_TYPE_OR)
	{
		if (tnode->is_subshell)
			return (str_dup("(s)||"));
		else
			return (str_dup("||"));
	}
	else if (tnode->type == E_NODE_TYPE_AND)
	{
		if (tnode->is_subshell)
			return (str_dup("(s)&&"));
		else
			return (str_dup("&&"));
	}
	return (NULL);
}

t_anode	*_build_ascii_tree_recursive(t_ast *tnode)
{
	t_anode	*anode;

	if (tnode == NULL)
		return (NULL);
	anode = uti_calloc(1, sizeof(t_anode));
	anode->left = _build_ascii_tree_recursive(tnode->left);
	anode->right = _build_ascii_tree_recursive(tnode->right);
	anode->line_nb = 0;
	if (anode->left != NULL)
		anode->left->parent_dir = -1;
	if (anode->right != NULL)
		anode->right->parent_dir = 1;
	if (tnode->type == E_NODE_TYPE_COMMAND)
		set_label(anode, tnode);
	else
	{
		anode->label = uti_calloc(2, sizeof(char *));
		anode->label[0] = _set_sep_label(tnode);
		anode->lab_width = str_len(anode->label[0]);
		anode->lab_height = 1;
	}
	return (anode);
}

t_anode	*build_ascii_tree(t_ast *tnode)
{
	t_anode	*anode;

	if (tnode == NULL)
		return (NULL);
	anode = _build_ascii_tree_recursive(tnode);
	anode->parent_dir = 0;
	return (anode);
}
