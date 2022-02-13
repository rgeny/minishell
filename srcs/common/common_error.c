/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 21:14:11 by buschiix          #+#    #+#             */
/*   Updated: 2022/02/13 18:00:08 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

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
	if (msg1 != NULL || msg2 != NULL || cmd != NULL)
		str_print_stderr("minishell: ");
	uti_interactive(INTERACTIVE_PRINT_LINE);
	str_print_stderr(cmd);
	str_print_stderr(msg1);
	str_print_stderr(msg2);
	if (msg1 != NULL || msg2 != NULL || cmd != NULL)
		str_print_stderr("\n");
	_error(ERROR_SET, return_value);
	return (return_value);
}
