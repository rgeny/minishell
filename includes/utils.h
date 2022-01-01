/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 17:26:48 by rgeny             #+#    #+#             */
/*   Updated: 2022/01/01 00:55:49 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdio.h>
# include <stdlib.h>
# include "env.h"

int		uti_min(int a, int b);
void	*uti_calloc(size_t count, size_t size);
void	uti_bzero(void *s, size_t n);
char	*uti_itoa(int n);
int		uti_ato_i(char *s);
long	uti_ato_l(char *s);
int		uti_isdigit(char *s);
char	*uti_readline(t_env *env);
#endif