/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 14:08:06 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/03 13:38:04 by buschiix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STR_H
# define STR_H

char	*str_dup(const char *s);
char	*str_ndup(const char *s, int n);
int		str_cmp(char *s1, char *s2);
int		str_ncmp(const char *s1, const char *s2, unsigned int n);
int		str_lcmp(char *s1, char *s2, int l);
char	*str_join(const char *s1, const char *s2, char c);
char	**str_split(char *s, char *charset);
char	**str_split_first(char *s, char c);
int		str_clen(const char *s, char c);
int		str_len(const char *s);
int		str_llen(char **s);
int		str_len_alnum(const char *s);
void	str_free(char *s);
void	str_free_list(char **s);
#endif
