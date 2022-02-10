/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_cmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 21:03:59 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/07 12:12:33 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	str_cmp(const char *s1, const char *s2)
{
	int	i;

	if (!s1 || !s2)
		return (-1);
	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int	str_ncmp(const char *s1, const char *s2, unsigned int n)
{
	unsigned int	i;

	if (n == 0 || !s1 || !s2)
		return (0);
	i = 0;
	while (i < n && s1[i] && s1[i] == s2[i])
		i++;
	if (i == n)
		i--;
	return ((int)((unsigned char)s1[i] - (unsigned char)s2[i]));
}

int	str_lcmp(char *s1, char *s2, int l)
{
	int	i;

	if (!l || !s1 || !s2)
		return (0);
	i = 0;
	while (s1[i] && i < l && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}
