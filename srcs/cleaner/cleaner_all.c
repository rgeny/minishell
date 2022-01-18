/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 14:49:40 by tokino            #+#    #+#             */
/*   Updated: 2022/01/18 14:50:29 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cleaner.h"

void	clean_all(t_data *data)
{
	str_free(data->pwd);
	env_del_all(data->env);
	lexer_free_tokens(&data->tokens);
}
