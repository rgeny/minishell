/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_readline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 00:32:29 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/13 14:16:48 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

char	*exe_readline(void)
{
	char	*ret;
	int		fdout;

	fdout = dup(STDOUT_FILENO);
	uti_interactive(INTERACTIVE_MOVE_STDERR);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	ret = readline("minishell$ ");
	dup2(fdout, STDOUT_FILENO);
	close(fdout);
	uti_interactive(INTERACTIVE_MOVE_STDERR);
	if (ret && ret[0])
		add_history(ret);
	return (ret);
}
