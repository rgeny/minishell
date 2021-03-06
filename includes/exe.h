/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 18:04:11 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/13 12:19:57 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXE_H
# define EXE_H
# include <fcntl.h> 
# include <readline/history.h>
# include "t_data.h"
# include "builtin.h"
# include "expander.h"
# include "sys/wait.h"
# include "carg.h"

void	exe_builtin(char **cmd, char **args, t_data *data);
void	exe_out_process(t_command *cmd, char **args, t_data *data);
char	*exe_readline(void);
void	exe_main(t_ast *ast, t_data *data);
void	exe_redir(t_redir *redir, int fd_heredoc, t_data *data);
void	exe_pipe(t_ast *ast, t_data *data);
void	exe_cmd(t_ast *ast, t_data *data);
void	exe_subshell(t_ast *ast, t_data *data);
#endif
