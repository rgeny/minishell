/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buschiix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 21:14:11 by buschiix          #+#    #+#             */
/*   Updated: 2022/01/06 21:19:28 by buschiix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "str.h"
#include "utils.h"
#include "struct.h"

void	print_error(char *cmd, char *message1, char *message2, t_data *data)
{
	char	*line;

	write(2, "minishell: ", 11);
	if (!data->interactive.is_interactive)
	{
		write(2, "line ", 5);
		line = uti_itoa(data->interactive.line);
		write(2, line, str_len(line, 0));
		write(2, ": ", 2);
		free(line);
	}
	write(2, cmd, str_len(cmd, 0));
	if (message1)
		write(2, message1, str_len(message1, 0));
	if (message2)
		write(2, message2, str_len(message2, 0));
}
