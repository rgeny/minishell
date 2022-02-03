/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_ast.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buschiix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 13:25:34 by buschiix          #+#    #+#             */
/*   Updated: 2022/02/03 13:35:00 by buschiix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_AST_H
# define T_AST_H
# include "sys/types.h"

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
	pid_t	pid;
	int		redir_nb;
	int		arg_nb;
	int		fd_in;
	int		fd_out;
}	t_command;

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
#endif
