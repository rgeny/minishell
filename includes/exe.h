/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 18:04:11 by rgeny             #+#    #+#             */
/*   Updated: 2022/01/28 10:12:17 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXE_H
# define EXE_H
# include "struct.h"

void	exe_builtin(char **cmd, t_data *data);
void	exe_out_process(char **cmd, t_data *data);
char	*exe_readline(t_data *data);
void	exe_main(t_node *cmd, t_data *data);
void	exe_redir(t_command *cmd);
void	exe_pipe(t_node *cmd, t_data *data);
void	exe_cmd(t_node *cmd, t_data *data);
#endif
