/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 18:04:11 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/03 13:37:24 by buschiix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXE_H
# define EXE_H
# include "t_data.h"

void	exe_builtin(char **cmd, t_data *data);
void	exe_out_process(t_command *cmd, t_data *data);
char	*exe_readline(t_data *data);
void	exe_main(t_node *cmd, t_data *data);
void	exe_redir(t_command *cmd);
void	exe_pipe(t_node *cmd, t_data *data);
void	exe_cmd(t_node *cmd, t_data *data);
#endif
