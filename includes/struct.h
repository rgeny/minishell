/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 18:28:18 by buschiix          #+#    #+#             */
/*   Updated: 2022/01/30 18:02:09 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

// LEXER STRUCTS
typedef enum e_token_type {
	E_TOKEN_TYPE_WORD,
	E_TOKEN_TYPE_OPERATOR,
	E_TOKEN_TYPE_REDIRECTION,
	E_TOKEN_TYPE_PIPE,
	E_TOKEN_TYPE_OR,
	E_TOKEN_TYPE_AND
}	t_token_type;

typedef struct s_token {
	char			*content;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

// COMMAND STRUCTS
typedef enum e_redir_type {
	E_REDIR_TYPE_STDIN,
	E_REDIR_TYPE_STDOUT,
	E_REDIR_TYPE_HEREDOC,
	E_REDIR_TYPE_APPEND
}	t_redir_type;

typedef struct s_redir{
	t_redir_type	type;
	char			*path;
}	t_redir;

typedef struct s_carg {
	char			*content;
	struct s_carg	*next;
}	t_carg;

typedef struct s_command {
	char	**args; // NULL terminated // TO DEL
	t_carg	*cargs;
	t_redir	*redirections;
	int		redir_nb;
	int		arg_nb;
	int		fd_in;
	int		fd_out;
}	t_command;

// AST
typedef enum s_node_type {
	E_NODE_TYPE_COMMAND,
	E_NODE_TYPE_PIPE
	// TODO : Add &&/|| types for bonuses
}	t_node_type;

typedef struct s_node {
	t_node_type		type;
	t_command		*command; // NULL except for leaf
	struct s_node	*left; // NULL if leaf
	struct s_node	*right; // NULL if leaf
}	t_node;

// ENV STRUCT
typedef struct s_env
{
	struct s_env	*next;
	struct s_env	*prev;
	char			*name;
	char			*value;
}					t_env;

typedef struct s_interactive
{
	unsigned long	line;
	int				is_interactive;
}					t_interactive;

typedef struct s_data
{
	t_env			*env;
	t_token			*tokens;
	t_node		*ast_root;
	int				ret;
	char			*pwd;
	t_interactive	interactive;
}					t_data;

#endif
