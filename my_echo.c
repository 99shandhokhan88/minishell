/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzashev <vzashev@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:01:57 by vzashev           #+#    #+#             */
/*   Updated: 2024/05/02 22:18:44 by vzashev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Function: my_echo
 * ------------------
 * Displays the arguments passed to the function.
 *
 * args: An array containing the command and arguments to be echoed.
 */

void	my_echo(char **args)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	g_exit = 0;
	while (args[i] && !comp_str(args[i], "-n") && i++)
		n_flag = 1;
	while (args[i])
	{
		write(1, args[i], len_str(args[i]));
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!n_flag)
		write(1, "\n", 1);
}
