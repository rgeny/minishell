/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_is.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buschiix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 22:47:29 by buschiix          #+#    #+#             */
/*   Updated: 2022/01/08 17:38:55 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	uti_is_in_charset(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

int	uti_isdigit(char *s)
{
	int	i;

	i = 0;
	if (!s[0])
		return (1);
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	uti_is_valid_var_name(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '=')
	{
		if (!((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z')
			|| s[i] == '_' || (i && s[i] >= '0' && s[i] <= '9')))
			return (0);
		i++;
	}
	if (!i)
		return (0);
	return (1);
}

int	uti_isalnum(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
		return (IS_ALPHA);
	else if (c >= '0' && c <= '9')
		return (IS_NUM);
	else
		return (IS_OTHER);
}
