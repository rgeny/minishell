/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_asciitree_builder.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 16:39:54 by tokino            #+#    #+#             */
/*   Updated: 2022/02/01 19:26:12 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_print.h"

char	*_cargs_to_str(t_carg *cargs)
{
	int		len;
	t_carg	*tmp;
	char	*str;

	len = 0;
	tmp = cargs;
	while (tmp)
	{
		len += str_len(tmp->content) + 1;
		tmp = tmp->next;
	}
	str = uti_calloc(len, sizeof(char));
	tmp = cargs;
	len = 0;
	while (tmp)
	{
		mem_cpy(str + len, tmp->content, str_len(tmp->content));
		len += str_len(tmp->content);
		tmp = tmp->next;
		if (tmp)
			mem_cpy(str + len++, " ", 1);
	}
	return (str);
}

char	*_redir_to_str(t_redir redir)
{
	char	*str;
	int		i;

	i = 2;
	str = uti_calloc(str_len(redir.path) + 4, sizeof(char));
	if (redir.type == E_REDIR_TYPE_APPEND)
	{
		i++;
		mem_cpy(str, ">> ", 3);
	}
	else if (redir.type == E_REDIR_TYPE_HEREDOC)
	{
		i++;
		mem_cpy(str, "<< ", 3);
	}
	else if (redir.type == E_REDIR_TYPE_STDIN)
		mem_cpy(str, "< ", 2);
	else
		mem_cpy(str, "> ", 2);
	mem_cpy(str + i, redir.path, str_len(redir.path));
	return (str);
}

void	_set_label(t_anode *anode, t_node *tnode)
{
	int	redir;

	anode->label = uti_calloc(tnode->command->redir_nb + 2, sizeof(char *));
	anode->label[0] = _cargs_to_str(tnode->command->cargs);
	anode->lab_width = str_len(anode->label[0]);
	redir = 0;
	while (redir < tnode->command->redir_nb)
	{
		anode->label[redir + 1] = \
			_redir_to_str(tnode->command->redirections[redir]);
		anode->lab_width = \
			uti_max(anode->lab_width, str_len(anode->label[redir + 1]));
		redir++;
	}
	anode->lab_height = tnode->command->redir_nb + 1;
}

t_anode	*_build_ascii_tree_recursive(t_node *tnode)
{
	t_anode	*anode;

	if (tnode == NULL)
		return (NULL);
	anode = malloc(sizeof(t_anode));
	anode->left = _build_ascii_tree_recursive(tnode->left);
	anode->right = _build_ascii_tree_recursive(tnode->right);
	anode->line_nb = 0;
	if (anode->left != NULL)
		anode->left->parent_dir = -1;
	if (anode->right != NULL)
		anode->right->parent_dir = 1;
	if (tnode->type == E_NODE_TYPE_COMMAND)
	{
		_set_label(anode, tnode);
	}
	else if (tnode->type == E_NODE_TYPE_PIPE)
	{
		anode->label = uti_calloc(2, sizeof(char *));
		anode->label[0] = str_dup("PIPE");
		anode->lab_width = str_len(anode->label[0]);
		anode->lab_height = 1;
	}
	return (anode);
}

t_anode	*build_ascii_tree(t_node *tnode)
{
	t_anode	*anode;

	if (tnode == NULL)
		return (NULL);
	anode = _build_ascii_tree_recursive(tnode);
	anode->parent_dir = 0;
	return (anode);
}
