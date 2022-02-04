/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_interactive.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buschiix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 11:18:30 by buschiix          #+#    #+#             */
/*   Updated: 2022/02/04 20:53:28 by buschiix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include "t_interactive.h"
#include "utils.h"
#include "str.h"

static void	_init(t_interactive *interactive)
{
	interactive->line = 0;
	interactive->is_interactive = isatty(0) && isatty(1) && isatty(2);
}

static void	_dup_stderr(void)
{
	static int	fd_null = FD_DFL_VALUE;
	static int	fd_error = FD_DFL_VALUE;

	if (fd_error < 0)
	{
		fd_null = open(PATH_NULL, O_WRONLY);
		fd_error = dup(STDERR_FILENO);
		dup2(fd_null, STDERR_FILENO);
		close(fd_null);
		uti_interactive(INTERACTIVE_INCR);
	}
	else
	{
		dup2(fd_error, STDERR_FILENO);
		close(fd_error);
		fd_error = FD_DFL_VALUE;
	}
}

static void	_print_line(unsigned long line)
{
	char	*str_line;

	str_line = uti_itoa(line);
	str_print_stderr("line ");
	str_print_stderr(str_line);
	str_print_stderr(": ");
	str_free(str_line);
}

unsigned long	uti_interactive(t_cmd_interactive cmd)
{
	static t_interactive	interactive;

	if (cmd == INTERACTIVE_INIT)
		_init(&interactive);
	else if (cmd == INTERACTIVE_INCR)
		interactive.line++;
	else if (cmd == INTERACTIVE_RETURN_IS_IT)
		return (interactive.is_interactive);
	else if (cmd == INTERACTIVE_PRINT_LINE && !interactive.is_interactive)
		_print_line(interactive.line);
	else if (cmd == INTERACTIVE_MOVE_STDERR && !interactive.is_interactive)
		_dup_stderr();
	return (cmd);
}
