/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_space_redir.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 12:41:18 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/10 12:54:41 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

bool	expand_space_redir(t_redir *redir)
{
	char	**word_list;

	if (count_word(redir->path) > 1)
		return (false);
	word_list = split_word(redir->path);
	str_free(&redir->path);
	redir->path = str_dup(word_list[0]);
	str_free_list(&word_list);
	return (true);
}
