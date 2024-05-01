/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzashev <vzashev@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:23:27 by vzashev           #+#    #+#             */
/*   Updated: 2024/05/01 18:27:50 by vzashev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_minus(t_data *data)
{
	if (var_index("OLDPWD=", data) < 0
		|| chdir((strchr(data->env[var_index("OLDPWD=", data)], '=')
				+ 1)) == -1)
		return (0);
	change_pwd(data);
	return (1);
}

int	cd_alone(t_data *data)
{
	if (var_index("HOME=", data) < 0
		|| chdir((strchr(data->env[var_index("HOME=", data)], '=') + 1)) == -1)
		return (0);
	change_pwd(data);
	return (1);
}

int	cd_path(char **args, t_data *data)
{
	if (chdir(args[1]) == -1)
		return (0);
	change_pwd(data);
	return (1);
}

void	handle_cd(char **args, t_data *data)
{
	if (args[1] && args[2])
		return (error_sentence("cd: too many arguments\n", 1));
	else if (!args[1])
	{
		if (!cd_alone(data))
			return (error_sentence("cd: HOME: is undefined\n", 1));
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		if (!cd_minus(data))
			return (error_sentence("cd: OLDPWD is undefined\n", 1));
	}
	else
	{
		if (!cd_path(args, data))
			return (error_sentence("cd: no such file or directory\n", 1));
	}
	g_exit = 0;
}
