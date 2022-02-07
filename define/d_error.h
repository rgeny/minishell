/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_error.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 21:38:11 by buschiix          #+#    #+#             */
/*   Updated: 2022/02/07 18:57:54 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef D_ERROR_H
# define D_ERROR_H

/*	Allowed functions error 	*/
# define GETCWD "getcwd: command has failed"

/*	global error	*/
# define TOO_MANY_ARGS "too many arguments"
# define NO_FILE ": No such file or directory"
# define BAD_IDENTIFIER ": not a valid identifier"
# define MALLOC_ERROR "Cannot allocate memory"

/*  Syntax error    */
# define TOKEN_ERROR    "Syntax error near unexpected token '" 
# define QUOTE_ERROR    "Syntax error: Please close all your quotes\n"

/*	env error	*/
# define ENV_HOME "HOME"
# define ENV_PWD "PWD"
# define ENV_OLDPWD "OLDPWD"
# define ENV_CDPATH "CDPATH"
# define ENV_SHLVL "SHLVL"

/*	cd error	*/
# define CD "cd: "
# define CD_NOT_SET " not set"

/*	exit error	*/
# define EXIT "exit: "
# define NUMBERED_ARG ": numbered argument is necessary"

/*	export error	*/
# define EXPORT "export: "

/*	pwd error	*/
# define PWD "pwd: "
# define BAD_OPT ": invalid option\npwd: usage: pwd"
# define DOUBLE_HYPHEN "--"

/*	unset error	*/
# define UNSET "unset: "

/*	expander error	*/
# define EXPAND_ASTERISK "asterisk: "

/*	heredoc error	*/
# define HEREDOC "heredoc: "
# define SIG_EOF "delimited by the signal EOF instead of word: "

/*	signal error	*/
# define SIG_ERROR 128
#endif
