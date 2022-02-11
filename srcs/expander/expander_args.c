/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 12:38:29 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/11 21:12:32 by buschiix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void	expand_args(t_command *cmd, t_carg *args, t_data *data, int *arg_n)
{
	t_carg	*prev;
	t_carg	*next;

	prev = NULL;
	while (args)
	{
		if (expand_var(&args->content, data->env, false))
		{
			(*arg_n)++;
			//printf("t1 : %s\n", args->content);
			expand_space_carg(args);
			//printf("t2 : %s\n", args->content);
			if (str_len(args->content) != str_clen(args->content, '*'))
				expand_asterisk(cmd, args, NULL);
			expand_quote(args->content);
			prev = args;
			args = args->next;
		}
		else
			carg_del_one(&args, cmd);
	}
}
