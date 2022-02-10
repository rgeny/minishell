/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_ast.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 13:25:34 by buschiix          #+#    #+#             */
/*   Updated: 2022/02/10 12:25:27 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_AST_H
# define T_AST_H

# include <stdbool.h>
# include "sys/types.h"
# include "t_lexer.h"
# include "t_env.h"

typedef struct s_ast_constructor
{
	t_token	*tokens;
	t_env	*env;
}	t_ast_constructor;

typedef enum e_redir_type {
	E_REDIR_TYPE_STDIN,
	E_REDIR_TYPE_STDOUT,
	E_REDIR_TYPE_HEREDOC,
	E_REDIR_TYPE_APPEND
}	t_redir_type;

typedef struct s_redir{
	t_redir_type	type;
	char			*path;
	struct s_redir	*next;
}	t_redir;

typedef struct s_carg {
	char			*content;
	struct s_carg	*next;
}	t_carg;

typedef struct s_command {
	t_carg	*cargs;
	t_redir	*redirections;
	pid_t	pid;
	int		arg_nb; // to delete
	int		fd_heredoc;
	int		last_return;
}	t_command;

typedef enum s_node_type {
	E_NODE_TYPE_COMMAND,
	E_NODE_TYPE_PIPE,
	E_NODE_TYPE_AND,
	E_NODE_TYPE_OR
}	t_node_type;

typedef struct s_ast {
	t_node_type		type;
	t_command		*cmd;
	struct s_ast	*left;
	struct s_ast	*right;
	bool			is_subshell;
	pid_t			pid;
}	t_ast;
#endif
