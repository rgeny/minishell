/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_readline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 00:32:29 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/04 23:45:51 by buschiix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <fcntl.h>
#include <dirent.h>
#include "str.h"
#include "env.h"
#include "error.h"
#include "utils.h"

static int	_cmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1)
		return (0);
	while (s1[i] && s1[i] == s2[i])
		i++;
	if (!s1[i])
		return (i);
	return (0);
}

static void	_cursor_error(void)
{
	if (uti_interactive(INTERACTIVE_RETURN_IS_IT))//data->interactive.is_interactive)
	{
		if (!g_last_return)
			write(1, "\033[32m\033[01m> ", 12);
		else
			write(1, "\033[31m\033[01m> ", 12);
	}
}

static char	*_prompt(t_data *data)
{
	char	path[PATH_MAX + 1];
	t_env	*pwd;
	int		ret;
	char	*tmp;
	char	*prompt;

	tmp = getcwd(path, PATH_MAX + 1);
	prompt = path;
	if (!tmp)
		prompt = data->pwd;
	pwd = env_find_var(data->env, "HOME");
	ret = 0;
	if (pwd)
		ret = _cmp(pwd->value, prompt);
	if (ret)
		tmp = str_join(PROMPT, &prompt[ret], '~');
	else
		tmp = str_join(PROMPT, prompt, 0);
	prompt = str_join(tmp, " \033[37m\033[00m", 0);
	str_free(tmp);
	return (prompt);
}

char	*exe_readline(t_data *data)
{
	char	*prompt;
	char	*ret;
	int		fdout;

	_cursor_error();
	prompt = _prompt(data);
	fdout = dup(1);
//	_non_interactive(&data->interactive);
	uti_interactive(INTERACTIVE_MOVE_STDERR);
	dup2(2, 1);
	ret = readline(prompt);
	dup2(fdout, 1);
	close(fdout);
	uti_interactive(INTERACTIVE_MOVE_STDERR);
	//_non_interactive(&data->interactive);
	str_free(prompt);
	return (ret);
}
