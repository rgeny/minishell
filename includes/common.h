/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 17:26:48 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/13 12:00:47 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H
# include <stdlib.h>
# include <stdbool.h> 
# include <fcntl.h>
# include "env.h"
# include "t_interactive.h"
# include "error.h"

int				uti_min(int a, int b);
int				uti_max(int a, int b);

void			uti_bzero(void *s, size_t n);

char			*uti_itoa(int n);
int				uti_atoi(char *s);
long			uti_atol(char *s);

bool			uti_isdigit(char *s);
int				uti_isalnum(char c);
int				uti_is_in_charset(char c, char *charset);
bool			uti_is_valid_name(char *s);

void			uti_quicksort(int start, int end, char **s);

unsigned long	uti_interactive(t_cmd_interactive cmd);

void			uti_free(void **p);
void			*uti_calloc(size_t count, size_t size);

void			close_fd(int *fd, int dfl_value);
void			dup_and_close(int *fd, int dfl_value);
#endif
