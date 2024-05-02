/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzashev <vzashev@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 18:01:03 by vzashev           #+#    #+#             */
/*   Updated: 2024/05/02 22:18:42 by vzashev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Function: my_cd
 * ----------------
 * Changes the current directory based on the given arguments.
 *
 * args: An array containing the command and directory path arguments.
 * s_hell: A pointer to the shell structure.
 */

void	my_cd(char **args, t_mini *s_hell)
{
	if (args[2])
		return (print_error("Error cd: not corrrect arguments!\n", 1));
	else if (!args[1])
	{
		if (!cd_one(s_hell))
			return (print_error("Error cd: HOME: undefined!\n", 1));
	}
	else if (comp_str(args[1], "-") == 0)
	{
		if (!cd_two(s_hell))
			return (print_error("Error cd: PWD: undefined!\n", 1));
	}
	else
	{
		if (!cd_pwd(args, s_hell))
			return (print_error("Error cd: no such file or directory!\n", 1));
	}
	g_exit = 0;
}
