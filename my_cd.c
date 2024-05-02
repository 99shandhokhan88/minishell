/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzashev <vzashev@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:23:27 by vzashev           #+#    #+#             */
/*   Updated: 2024/05/02 02:37:21 by vzashev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_one(t_mini *s_hell)
{
	if (envv_index("HOME=", s_hell) < 0
		|| chdir((str_char(s_hell->envv[envv_index("HOME=", s_hell)], '=') + 1))
		== -1)
		return (0);
	change_pwd(s_hell);
	return (1);
}

int	cd_two(t_mini *s_hell)
{
	if (envv_index("OLDPWD=", s_hell) < 0
		|| chdir((str_char(s_hell->envv[envv_index("OLDPWD=", s_hell)], '=')
				+ 1)) == -1)
		return (0);
	change_pwd(s_hell);
	return (1);
}

int	cd_pwd(char **args, t_mini *s_hell)
{
	if (chdir(args[1]) == -1)
		return (0);
	change_pwd(s_hell);
	return (1);
}

void	my_cd(char **args, t_mini *s_hell)
{
	if (args[2])
		return (print_error("Error cd: too many arguments!\n", 1));
	else if (!args[1])
	{
		if (!cd_one(s_hell))
			return (print_error("Error cd: HOME: is undefined!\n", 1));
	}
	else if (comp_str(args[1], "-") == 0)
	{
		if (!cd_two(s_hell))
			return (print_error("Error cd: PWD: is undefined!\n", 1));
	}
	else
	{
		if (!cd_pwd(args, s_hell))
			return (print_error("cd: no such file or directory!\n", 1));
	}
	g_exit_status = 0;
}
