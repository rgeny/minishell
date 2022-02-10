/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 15:08:02 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/10 11:18:14 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H
# include <readline/readline.h>
# include "d_global.h"
# include "env.h"
# include "minishell_signal.h"
# include "mem.h"
# include "lst.h"

typedef struct dirent	t_dirent;
void	expander_main(t_data *data, t_ast *ast);
int		expand_heredoc(char *delimiter, t_env *env);
char	*expand_path(char *cmd, t_env *env);
bool	expand_var(char **word, t_env *env);
void	expand_quote(char *s);
bool	expand_asterisk(t_command *cmd, t_carg *args, t_redir *redir);
char	**asterisk_dir_list(void);
bool	asterisk_cmp(char *word, char *dir);
void	expand_space_carg(t_carg *args);
bool	expand_space_redir(t_redir *redir);
void	expand_args(t_command *cmd, t_carg *args, t_data *data);
void	expand_redir(t_command *cmd, t_redir *redir, t_data *data);
#endif
