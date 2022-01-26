/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 15:08:02 by rgeny             #+#    #+#             */
/*   Updated: 2022/01/26 20:04:30 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

char *	expander_path(char **cmd, t_env *env);
void	expander_var(char **cmd, t_data *data);
char	*expander_asterisk(char *rl);
char	**asterisk_dir_list(void);
#endif
