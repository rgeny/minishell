/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carg.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 14:55:55 by tokino            #+#    #+#             */
/*   Updated: 2022/02/10 16:08:16 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CARG_H
# define CARG_H

# include "t_ast.h"
# include "error.h"

void	carg_add_back(t_carg **lst, t_carg *new);
void	carg_new_after(t_carg *current, char *new_content);
void	carg_del_one(t_carg **args, t_command *cmd);
void	carg_redirection_add_back(t_redir **lst, t_redir *new);
char	**carg_switch_to_list(t_carg *lst, int n_arg);
#endif
