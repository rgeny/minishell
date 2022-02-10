/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 17:55:28 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/10 18:12:18 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IS_H
# define IS_H
# include <stdbool.h>
# include "t_is.h"

bool	is_in_charset(char c, char *charset);
bool	is_digit(char *s);
bool	is_valid_name(char *s);
int		is_alnum(char c);
#endif
