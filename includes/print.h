/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buschiix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 21:18:20 by buschiix          #+#    #+#             */
/*   Updated: 2022/01/07 19:49:16 by buschiix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_H
# define PRINT_H
# include "struct.h"

void	print_error(char *cmd, char *message1, char *message2, t_data *data);
void	print_fd(const char *s, int fd);
#endif
