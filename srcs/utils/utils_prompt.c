/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 00:32:29 by rgeny             #+#    #+#             */
/*   Updated: 2022/01/01 00:58:12 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include "str.h"
#include "env.h"

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

	getcwd(path, PATH_CHAR_MAX + 1);
	pwd = env_find(env, "HOME");
	ret = 0;
	if (pwd)
		ret = static_cmp(pwd->value, path);
	if (ret)
		tmp = str_join(PROMPT, &path[ret], '~');
	else
		tmp = str_join(PROMPT, path, 0);
	prompt = str_join(tmp, "$ ", 0);
	free(tmp);
	return (prompt);
}

char	*uti_readline(t_env *env)
{
	char	*prompt;
	char	*ret;

	prompt = static_prompt(env);
	ret = readline(prompt);
	free(prompt);
	return (ret);
}
