/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 17:26:48 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/05 14:23:49 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include <stdlib.h>
# include "env.h"
# include "t_interactive.h"
# include "error.h"

typedef enum e_iswhat
{
	IS_OTHER,
	IS_ALPHA,
	IS_NUM,
}	t_iswhat;
int				uti_min(int a, int b);
int				uti_max(int a, int b);
void			*uti_calloc(size_t count, size_t size);
void			uti_bzero(void *s, size_t n);
char			*uti_itoa(int n);
int				uti_ato_i(char *s);
long			uti_ato_l(char *s);
int				uti_isdigit(char *s);
int				uti_isalnum(char c);
int				uti_is_in_charset(char c, char *charset);
int				uti_is_valid_var_name(char *s);
void			uti_quicksort(int start, int end, char **s);
unsigned long	uti_interactive(t_cmd_interactive cmd);
#endif
