/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_signal.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 20:37:18 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/01 14:51:32 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_SIGNAL_H
# define MINISHELL_SIGNAL_H

void	signal_current(void);
void	signal_ignore(void);
void	signal_fork(void);
void	signal_heredoc(void);
#endif
