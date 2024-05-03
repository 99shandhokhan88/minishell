/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzashev <vzashev@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 18:01:03 by vzashev           #+#    #+#             */
/*   Updated: 2024/05/03 19:01:30 by vzashev          ###   ########.fr       */
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
	if (!args[1])
	{
		if (!cd_one(s_hell))
			print_error("minishell$: HOME: undefined\n", 1);
	}
	else if (!args[2])
	{
		if (!comp_str(args[1], "-"))
		{
			if (!cd_two(s_hell))
				print_error("minishell$: PWD: undefined\n", 1);
		}
		else
		{
			if (!cd_pwd(args, s_hell))
				print_error("minishell$: cd: no such file or directory\n", 1);
		}
	}
	else
		print_error("minishell$: cd: not correct arguments\n", 1);
	g_exit = 0;
}
