/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 18:04:11 by rgeny             #+#    #+#             */
/*   Updated: 2022/01/07 20:02:01 by buschiix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXE_H
# define EXE_H

void	exe_builtin(char **cmd, t_data *data);
void	exe_out_process(char **cmd, t_data *data);
char	*exe_readline(t_data *data);
#endif
