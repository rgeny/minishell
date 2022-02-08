/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asterisk_cmp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 12:59:58 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/08 13:36:20 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static bool	_change_values(int *j, char **p, int i, int n_quote)
{
	*j += i;
	*p += n_quote;
	return (true);
}

static bool	_is_valid_name(char *word, char *dir, char **pt_word, int *j)
{
	int		i;
	int		n_quote;
	int		len;

	i = 0;
	n_quote = 0;
	while (word[i + n_quote] != '\0' && word[i + n_quote] != '*')
	{
		if (uti_is_in_charset(word[i + n_quote], QUOTES))
		{
			len = str_clen(&word[i + n_quote + 1], word[i + n_quote]);
			if (str_ncmp(&word[i + n_quote + 1], &dir[i], len) != 0)
				return (false);
			i += len;
			n_quote += 2;
		}
		else if (word[i + n_quote] != dir[i])
			return (false);
		else
			i++;
	}
	if (word[i + n_quote] == '*'
		|| (word[i + n_quote] == '\0' && dir[i] == '\0'))
		return (_change_values(j, pt_word, i, n_quote));
	return (false);
}

bool	asterisk_cmp(char *word, char *dir)
{
	int		i;
	int		quote;
	bool	asterisk;

	if (word[0] != '.' && dir[0] == '.')
		return (false);
	i = 0;
	asterisk = false;
	while (word[i] != '\0' || dir[i] != '\0')
	{
		if (word[i] == '*')
		{
			word += str_first_dif(&word[i], '*');
			asterisk = true;
		}
		else if (asterisk == true)
		{
			while (dir[i] && _is_valid_name(&word[i], &dir[i], &word, &i) == 0)
				dir++;
			asterisk = false;
		}
		else if (_is_valid_name(&word[i], &dir[i], &word, &i) == 0)
			return (0);
	}
	return (word[i] == '\0' && dir[i] == '\0');
}
