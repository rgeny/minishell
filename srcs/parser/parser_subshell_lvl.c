/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_subshell_lvl.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 17:26:50 by tokino            #+#    #+#             */
/*   Updated: 2022/02/06 18:05:05 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#define SET 0
#define GET 1

int _subshell_lvl(int mode, int lvl)
{
    static int subshell_lvl;

    if (mode == SET)
        subshell_lvl = lvl;
    return (subshell_lvl);
}

void    set_subshell_lvl(int lvl)
{
    _subshell_lvl(SET, lvl);
}

void    reset_subshell_lvl(void)
{
    set_subshell_lvl(0);
}

int get_subshell_lvl(void)
{
    return (_subshell_lvl(GET, 0));
}

void    increase_subshell_lvl(void)
{
    int current_lvl;

    current_lvl = _subshell_lvl(GET, 0);
    current_lvl++;
    _subshell_lvl(SET, current_lvl);
}

void    decrease_subshell_lvl(void)
{
    int current_lvl;

    current_lvl = _subshell_lvl(GET, 0);
    current_lvl--;
    _subshell_lvl(SET, current_lvl);
}
