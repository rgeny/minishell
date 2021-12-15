/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 14:08:06 by rgeny             #+#    #+#             */
/*   Updated: 2021/12/15 14:22:19 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STR_H
# define STR_H

char	*str_ndup(const char *s, int n);
char	*str_cmp(char *s1, char *s2);
char	**str_split(char *s, char *charset);
int		str_len(const char *s, char c);
#endif
