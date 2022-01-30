/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 14:55:55 by tokino            #+#    #+#             */
/*   Updated: 2022/01/30 15:23:38 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LST_H
# define LST_H

# include "struct.h"

void	lst_carg_add_back(t_carg **lst, t_carg *new);
void	lst_carg_add_after(t_carg *after, t_carg *new);

#endif