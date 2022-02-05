/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_error.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 21:38:11 by buschiix          #+#    #+#             */
/*   Updated: 2022/02/05 19:46:10 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef D_ERROR_H
# define D_ERROR_H

/*	Allowed functions error 	*/
# define GETCWD "getcwd: command has failed"

/*	global error	*/
# define TOO_MANY_ARGS "too many arguments"
# define NO_FILE ": No such file or directory"
# define MALLOC_ERROR "Cannot allocate memory"

/*	env error	*/
# define ENV_HOME "HOME"
# define ENV_PWD "PWD"
# define ENV_OLDPWD "OLDPWD"
# define ENV_CDPATH "CDPATH"

/*	cd error	*/
# define CD "cd: "
# define CD_NOT_SET " not set"

/*	exit error	*/
# define EXIT "exit: "
# define NUMBERED_ARG ": numbered argument is necessary"
#endif
