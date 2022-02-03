/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buschiix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 21:14:11 by buschiix          #+#    #+#             */
/*   Updated: 2022/02/03 12:31:04 by buschiix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "str.h"
#include "utils.h"
#include "struct.h"

int	print_error(char *cmd, char *message1, char *message2, int return_value)
{
	char	*line;

	write(2, "minishell: ", 11);
	if (!uti_interactive(INTERACTIVE_RETURN_IS_IT))
	{
		write(2, "line ", 5);
		line = uti_itoa(uti_interactive(INTERACTIVE_RETURN_LINE));
		write(2, line, str_len(line));
		write(2, ": ", 2);
		str_free(line);
	}
	if (cmd)
		write(2, cmd, str_len(cmd));
	if (message1)
		write(2, message1, str_len(message1));
	if (message2)
		write(2, message2, str_len(message2));
	return (return_value);
}
