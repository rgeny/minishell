/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 15:08:02 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/13 11:22:29 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H
# include <readline/readline.h>
# include "d_global.h"
# include "env.h"
# include "minishell_signal.h"
# include "mem.h"
# include "carg.h"

typedef t_command		t_cmd;
typedef struct dirent	t_dirent;
int		expand_heredoc(char *delimiter, t_env *env);
char	*expand_path(char *cmd, t_env *env);
bool	expand_var(char **word, t_env *env, bool is_sub_expand);
void	expand_quote(char *s);

void	expand_space_carg(t_carg *args);
bool	expand_space_redir(t_redir *redir);
int		count_word(char *s);
char	**split_word(char *s);

void	expand_args(t_command *cmd, t_carg *args, t_data *data, int *arg_n);
void	expand_redir(t_command *cmd, t_redir *redir, t_data *data);

bool	expand_asterisk(t_command *cmd, t_carg *args, t_redir *redir);
char	**asterisk_dir_list(void);
bool	asterisk_cmp(char *word, char *dir);
#endif
