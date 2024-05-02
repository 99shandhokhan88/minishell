/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzashev <vzashev@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:28:26 by vzashev           #+#    #+#             */
/*   Updated: 2024/05/02 01:37:58 by vzashev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_echo(char **args)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	g_exit_status = 0;
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
