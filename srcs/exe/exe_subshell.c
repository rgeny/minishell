/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_subshell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 03:48:59 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/10 03:50:28 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

void	exe_subshell(t_ast *ast, t_data *data)
{
	exe_main(ast, data);
	exit(g_last_return);
}
