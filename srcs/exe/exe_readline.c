/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_readline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 00:32:29 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/01 14:57:23 by rgeny            ###   ########.fr       */
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

static void	_curse_error(t_data *data)
{
	if (data->interactive.is_interactive)
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
	pwd = env_find(data->env, "HOME");
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

static void	_non_interactive(t_interactive *interactive)
{
	static int	fdnull = -1;
	static int	fderr = -1;

	if (!interactive->is_interactive)
	{
		if (fderr < 0)
		{
			fdnull = open("/dev/null", O_WRONLY);
			fderr = dup(2);
			dup2(fdnull, 2);
			close(fdnull);
			interactive->line++;
		}
		else
		{
			dup2(fderr, 2);
			close(fderr);
			fderr = -1;
		}
	}
}

char	*exe_readline(t_data *data)
{
	char	*prompt;
	char	*ret;
	int		fdout;

	_curse_error(data);
	prompt = _prompt(data);
	fdout = dup(1);
	_non_interactive(&data->interactive);
	dup2(2, 1);
	ret = readline(prompt);
	dup2(fdout, 1);
	close(fdout);
	_non_interactive(&data->interactive);
	str_free(prompt);
	return (ret);
}
