/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 14:08:06 by rgeny             #+#    #+#             */
/*   Updated: 2022/01/06 20:46:42 by buschiix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STR_H
# define STR_H
# include "struct.h"

char	*str_ndup(const char *s, int n);
int		str_cmp(char *s1, char *s2);
int		str_ncmp(const char *s1, const char *s2, unsigned int n);
char	*str_join(const char *s1, const char *s2, char c);
char	**str_split(char *s, char *charset);
char	**str_split_first(char *s, char c);
int		str_len(const char *s, char c);
int		str_llen(char **s);
void	str_free_string(char **s);
void	str_printfd(const char *s, int fd);
void	str_printerr(char *s1, char *s2, char *s3, char *s4);
void	str_print_error(char *cmd, char *message1, char *message2, t_data *data);
#endif
