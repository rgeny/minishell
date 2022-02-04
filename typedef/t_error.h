/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_error.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buschiix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 21:38:43 by buschiix          #+#    #+#             */
/*   Updated: 2022/02/04 21:45:57 by buschiix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_ERROR_H
# define T_ERROR_H

typedef enum e_error
{
	SUCCESS,
	ERROR_EXEC,
	ERROR_SYNTAX,
	ERROR_SET,
	ERROR_GET
}	t_error;
typedef enum e_signal
{
	SIGNAL_EOF=11,
	SIGNAL_ERROR=128
}	t_signal;
#endif
