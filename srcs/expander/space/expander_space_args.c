/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_space_args.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 12:44:33 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/10 16:09:17 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void	expand_space_carg(t_carg *args)
{
	char	**word_list;
	int		i;
	bool	is_first;

	word_list = split_word(args->content);
	i = 0;
	is_first = true;
	while (word_list[i])
	{
		if (is_first)
		{
			str_free(&args->content);
			args->content = str_dup(word_list[i]);
			is_first = false;
		}
		else
		{
			carg_new_after(args, word_list[i]);
			args = args->next;
		}
		i++;
	}
	str_free_list(&word_list);
}
