/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 14:34:28 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/01 14:53:56 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H
# define SUCCESS 0

extern int	g_last_return;
typedef enum e_signal
{
	SIGNAL_EOF=11,
	SIGNAL_ERROR=128
}	t_signal;
typedef enum e_builtin
{
	BUILTIN_ERR_EXEC=1,
	BUILTIN_ERR_SYNTAX
}	t_builtin;

/*
** Arrêt en cas de signal fatal : 128+signal
** Si la commande est trouvé mais non exécutable : 126
** Erreur lors du développement ou mise en place de redirection : > 0
** Builtin : 0(success), 1(erreur exec), 2(syntax error)
** Renvoie retour de la dernière commande ou autre chose en cas de syntax error.
*/
#endif
