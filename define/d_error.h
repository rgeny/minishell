/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_error.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 21:38:11 by buschiix          #+#    #+#             */
/*   Updated: 2022/02/05 14:45:49 by tokino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef D_ERROR_H
# define D_ERROR_H

/*	Allowed functions error 	*/
# define GETCWD "getcwd: command has failed\n"

/*	global error	*/
# define TOO_MANY_ARGS  "too many arguments\n"
# define NO_FILE        ": No such file or directory\n"
# define MALLOC_ERROR   "Cannot allocate memory\n"

/*  Syntax error    */
# define TOKEN_ERROR    "Syntax error near unexpected token '" 


/*	env error	*/
# define ENV_HOME "HOME"
# define ENV_PWD "PWD"
# define ENV_OLDPWD "OLDPWD"
# define ENV_CDPATH "CDPATH"

/*	cd error	*/
# define CD "cd: "
# define CD_NOT_SET " not set\n"
#endif
