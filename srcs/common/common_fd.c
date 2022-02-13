/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 11:44:40 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/13 12:00:49 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void	close_fd(int *fd, int dfl_value)
{
	if (*fd != dfl_value)
	{
		close(*fd);
		*fd = dfl_value;
	}
}

void	dup_and_close(int *fd, int dfl_value)
{
	if (*fd != dfl_value)
	{
		dup2(*fd, dfl_value);
		close_fd(fd, dfl_value);
	}
}
