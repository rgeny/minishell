/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_error.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 21:38:43 by buschiix          #+#    #+#             */
/*   Updated: 2022/02/05 14:47:33 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_ERROR_H
# define T_ERROR_H

typedef enum e_error
{
	SUCCESS,
	ERROR_EXEC=1,
	ERROR_MALLOC=1,
	ERROR_SYNTAX=2,
	ERROR_TOKEN=2,
	ERROR_SET,
	ERROR_GET
}	t_error;
typedef enum e_signal
{
	SIGNAL_EOF=11,
	SIGNAL_ERROR=128
}	t_signal;
#endif
