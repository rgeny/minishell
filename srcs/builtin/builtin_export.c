/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokino <tokino@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 18:35:26 by rgeny             #+#    #+#             */
/*   Updated: 2022/02/13 10:30:42 by rgeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	_print_env(t_data *data)
{
	char	**cpy;
	int		i;

	cpy = env_switch(data, true);
	if (cpy == NULL)
		return ;
	uti_quicksort(0, str_llen(cpy) - 1, cpy);
	i = 0;
	while (cpy[i] != NULL)
	{
		if (cpy[i][0] != '_' || cpy[i][1] != '=')
		{
			str_print_fd(EXPORT, data->pipefd[1]);
			str_print_fd_nl(cpy[i], data->pipefd[1]);
		}
		i++;
	}
	str_free_list(&cpy);
}

static void	_export_var(char **cmd, t_data *data)
{
	int		i;
	char	**var;

	i = 0;
	while (cmd[i] != NULL)
	{
		if (is_valid_name(cmd[i]))
		{
			var = str_split_first(cmd[i], '=');
			if (var != NULL && var[0] != NULL)
				env_new(&data->env, str_dup(var[0]), str_dup(var[1]));
			str_free_list(&var);
		}
		else
			error_print(EXPORT, cmd[i], BAD_IDENTIFIER, ERROR_EXEC);
		i++;
	}
}

int	builtin_export(char **cmd, t_data *data)
{
	if (cmd[0] == NULL)
		_print_env(data);
	else
		_export_var(cmd, data);
	return (error_get());
}
