/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buschiix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 21:18:20 by buschiix          #+#    #+#             */
/*   Updated: 2022/02/03 13:36:45 by buschiix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_H
# define PRINT_H

int		print_error(char *cmd, char *message1, char *message2, int return_value);
void	print_fd(const char *s, int fd);
#endif
