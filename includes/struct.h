/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 18:28:18 by buschiix          #+#    #+#             */
/*   Updated: 2022/01/15 13:02:22 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

// LEXER STRUCTS
typedef enum e_token_type {
	E_TOKEN_TYPE_WORD,
	E_TOKEN_TYPE_OPERATOR
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

typedef struct s_redir
{
	t_redir_type	type;
	char			*path;
}	t_redir;

typedef struct s_command {
	char	**args;
	t_redir	**redirections;
}	t_command;


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
	int				ret;
	char			*pwd;
	t_interactive	interactive;
}					t_data;

#endif
