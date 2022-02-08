/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 18:04:11 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/10 02:12:00 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXE_H
# define EXE_H
# include "t_data.h"
# include "builtin.h"

void	exe_builtin(char **cmd, char **args, t_data *data);
void	exe_out_process(t_command *cmd, t_data *data);
char	*exe_readline(t_data *data);
void	exe_main(t_ast *ast, t_data *data);
int		exe_redir(t_command *cmd);
void	exe_pipe(t_ast *ast, t_data *data);
void	exe_cmd(t_ast *ast, t_data *data);
#endif
