/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 14:55:55 by tokino            #+#    #+#             */
/*   Updated: 2022/02/09 12:51:38 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LST_H
# define LST_H

# include "t_ast.h"

void	lst_carg_add_back(t_carg **lst, t_carg *new);
void	lst_carg_add_after(t_carg *after, t_carg *new);
void	lst_new_after(t_carg *current, char *new_content);
void	lst_redirection_add_back(t_redir **lst, t_redir *new);

#endif
