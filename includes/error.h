/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 14:34:28 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/04 21:57:46 by buschiix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "t_error.h"
# include "d_error.h"

extern int	g_last_return;

void	error_reset(void);
int		error_get(void);
int		error_print(char *cmd, char *msg1, char *msg2, int return_value);
/*
** Arrêt en cas de signal fatal : 128+signal
** Si la commande est trouvé mais non exécutable : 126
** Erreur lors du développement ou mise en place de redirection : > 0
** Builtin : 0(success), 1(erreur exec), 2(syntax error)
** Renvoie retour de la dernière commande ou autre chose en cas de syntax error.
*/
#endif
