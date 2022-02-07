/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 21:14:11 by buschiix          #+#    #+#             */
/*   Updated: 2022/02/07 13:07:43 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "str.h"
#include "utils.h"
#include "struct.h"
#include "error.h"

static int	_error(int cmd, int return_value)
{
	static int	error = SUCCESS;

	if (cmd == ERROR_SET)
		error = return_value;
	return (error);
}

void	error_reset(void)
{
	_error(ERROR_SET, SUCCESS);
}

int	error_get(void)
{
	return (_error(ERROR_GET, SUCCESS));
}

bool	is_error(void)
{
	return (error_get() != SUCCESS);
}

int	error_print(char *cmd, char *msg1, char *msg2, int return_value)
{
	str_print_stderr("minishell: ");
	uti_interactive(INTERACTIVE_PRINT_LINE);
	str_print_stderr(cmd);
	str_print_stderr(msg1);
	str_print_stderr(msg2);
	write(STDERR_FILENO, "\n", 1);
	_error(ERROR_SET, return_value);
	return (return_value);
}
