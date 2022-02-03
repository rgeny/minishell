/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 15:08:02 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/03 13:36:15 by buschiix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H
# include "t_data.h"

void	expander_main(t_data * data, t_node *ast);
int		expander_heredoc(char *delimiter);
char *	expander_path(char *cmd, t_env *env);
void	expander_var(t_carg *cmd, t_data *data);
char	*expander_asterisk(char *rl);
char	**asterisk_dir_list(int b);
#endif
