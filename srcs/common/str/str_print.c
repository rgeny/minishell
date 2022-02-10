/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buschiix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 19:48:45 by buschiix          #+#    #+#             */
/*   Updated: 2022/02/10 18:29:47 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

void	str_print_fd(char *s, int fd)
{
	if (s)
		write(fd, s, str_len(s));
}

void	str_print_fd_nl(char *s, int fd)
{
	if (s)
	{
		write(fd, s, str_len(s));
		write(fd, "\n", 1);
	}
}

void	str_print_stderr(char *s)
{
	str_print_fd(s, STDERR_FILENO);
}
