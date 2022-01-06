/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_printerr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 22:25:33 by rgeny             #+#    #+#             */
/*   Updated: 2022/01/06 19:47:15 by buschiix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "str.h"
#include "struct.h"
#include "utils.h"

void	str_printerr(char *s1, char *s2, char *s3, char *s4)
{
	if (s1)
		write(2, s1, str_len(s1, 0));
	if (s2)
		write(2, s2, str_len(s2, 0));
	if (s3)
		write(2, s3, str_len(s3, 0));
	if (s4)
		write(2, s4, str_len(s4, 0));
}

int	str_print_error(char *cmd, char *message, t_data data, int ret)
{
	char	*line;

	write(2, "minishell: ", 11);
	if (!data.interactive.is_interactive)
	{
		write(2, "line ", 5);
		line = uti_itoa(data.interactive.line);
		write(2, line, str_len(line, 0));
		write(2, " : ", 3);
		free(line);
	}
	write(2, cmd, str_len(cmd, 0));
	write(2, ": ", 2);
	write(2, message, str_len(message, 0));
	write(2, "\n", 1);
	return (ret);
}
