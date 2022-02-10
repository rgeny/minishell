/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 15:08:49 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/10 18:16:23 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static char	*_find_var_value(char *word, t_env *env)
{
	char	*value;
	char	*name;

	if (word[0] == '?')
		return (uti_itoa(g_last_return));
	name = str_ndup(word, str_len_alnum(word));
	value = env_find_val(env, name);
	str_free(&name);
	return (str_dup(value));
}

static char	*_switch_name_to_value(char *prev, char *find, char *word, int len)
{
	char	*tmp;
	char	*new_value;

	tmp = str_join(prev, find, 0);
	new_value = str_join(tmp, &word[len], 0);
	if (new_value == NULL)
		new_value = uti_calloc(2, 1);
	str_free(&tmp);
	str_free(&find);
	return (new_value);
}

static void	_expand(char **word, t_env *env, int i)
{
	int		len;
	char	*prev_val;
	char	*new_val;
	char	*find;

	prev_val = str_ndup(word[0], i);
	len = str_len_alnum(&word[0][i + 1]);
	if (word[0][i + 1] == '?')
		len++;
	find = _find_var_value(&word[0][i + 1], env);
	if (find != NULL || len != 0)
	{
		new_val = _switch_name_to_value(prev_val, find, &word[0][i + 1], len);
		str_free(&word[0]);
		word[0] = new_val;
	}
	str_free(&prev_val);
}

bool	expand_var(char **word, t_env *env)
{
	int		i;

	i = 0;
	while (word[0][i] != '\0')
	{
		if (word[0][i] == '\'')
			i += str_clen(&word[0][i + 1], word[0][i]) + 1;
		if (word[0][i] == '$')
			_expand(word, env, i);
		if (word[0][i] != '\0'
			&& (word[0][i] != '$' || !is_alnum(word[0][i + 1])))
			i++;
	}
	return (word[0][0] != '\0');
}
