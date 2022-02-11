/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_space_tool.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 12:36:32 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/11 21:18:04 by buschiix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static int	_len_next_word(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != ' ')
	{
		if ((s[i] == '"' || s[i] == '\'')
			&& str_len(&s[i + 1]) != str_clen(&s[i + 1], s[i]))
			i += str_clen(&s[i + 1], s[i]) + 2;
		else
			i++;
	}
	return (i);
}

int	count_word(char *s)
{
	int	i;
	int	n_space;

	i = 0;
	n_space = 0;
	while (s[i])
	{
		if (s[i] == ' ')
			i += str_first_dif(&s[i], ' ');
		else
		{
			n_space++;
			i += _len_next_word(&s[i]);
		}
	}
	return (n_space);
}

static void	_fill_list(char *s, char **word_list)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == ' ')
			i += str_first_dif(&s[i], ' ');
		else
		{
			len = _len_next_word(&s[i]);
			word_list[j] = str_ndup(&s[i], len);
			j++;
			i += len;
		}
	}
}

char	**split_word(char *s)
{
	int		word_n;
	char	**word_list;

	word_n = count_word(s);
	word_list = uti_calloc(word_n + 1, sizeof(char *));
	if (word_list == NULL)
		return (NULL);
	_fill_list(s, word_list);
	return (word_list);
}
