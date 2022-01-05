/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_readline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 00:32:29 by rgeny             #+#    #+#             */
/*   Updated: 2022/01/05 18:48:54 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <fcntl.h>
#include "str.h"
#include "env.h"
#include "global.h"

static int	static_cmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	if (!s1[i])
		return (i);
	return (0);
}

static char	*static_prompt(t_env *env)
{
	char	path[PATH_CHAR_MAX + 1];
	t_env	*pwd;
	int		ret;
	char	*tmp;
	char	*prompt;

	tmp = getcwd(path, PATH_CHAR_MAX + 1);
	prompt = path;
	if (!tmp)
		prompt = glo_pwd(0, 0);
	pwd = env_find(env, "HOME");
	ret = 0;
	if (pwd)
		ret = static_cmp(pwd->value, prompt);
	if (ret)
		tmp = str_join(PROMPT, &prompt[ret], '~');
	else
		tmp = str_join(PROMPT, prompt, 0);
	prompt = str_join(tmp, "$ ", 0);
	free(tmp);
	return (prompt);
}

static void	static_non_interactive(void)
{
	static int	fdnull = -1;
	static int	fderr = -1;

	if ((!isatty(0) || !isatty(1) || !isatty(2)) && fderr < 0)
	{
		fdnull = open("/dev/null", O_WRONLY);
		fderr = dup(2);
		dup2(fdnull, 2);
		close(fdnull);
	}
	else if (fderr >= 0)
	{
		dup2(fderr, 2);
		close(fderr);
		fderr = -1;
	}
}

char	*uti_readline(t_env *env)
{
	char	*prompt;
	char	*ret;
	int		fdout;

	prompt = static_prompt(env);
	fdout = dup(1);
	static_non_interactive();
	dup2(2, 1);
	ret = readline(prompt);
	dup2(fdout, 1);
	close(fdout);
	static_non_interactive();
	free(prompt);
	return (ret);
}
