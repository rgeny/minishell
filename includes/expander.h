/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 15:08:02 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/09 12:23:26 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H
# include <readline/readline.h>
# include "d_global.h"
# include "env.h"
# include "minishell_signal.h"
# include "mem.h"

typedef struct dirent	t_dirent;
void	expander_main(t_data *data, t_ast *ast);
int		expand_heredoc(char *delimiter, t_data *data);
char	*expand_path(char *cmd, t_env *env);
void	expand_var(char **word, t_data *data);
void	expand_quote(char *s);
bool	expand_asterisk(t_command *cmd, t_carg *args, t_redir *redir);
char	**asterisk_dir_list(void);
bool	asterisk_cmp(char *word, char *dir);
#endif
