/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_printerr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 22:25:33 by rgeny             #+#    #+#             */
/*   Updated: 2021/12/31 22:27:59 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "str.h"

void	str_printerr(char *s1, char *s2, char *s3, char *s4)
{
	if (s1)
		write(2, s1, str_len(s1, 0));
	if (s2)
		write(2, s2, str_len(s2, 0));
	if (s3)
		write(2, s3, str_len(s3, 0));
	if (s4)
		write(2, s4, str_len(s4, 0));
}
