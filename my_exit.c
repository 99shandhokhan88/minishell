/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzashev <vzashev@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:44:43 by vzashev           #+#    #+#             */
/*   Updated: 2024/05/02 02:42:08 by vzashev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_exit(char **inputs, t_mini *s_hell)
{
	g_exit_status = 0;
	if (inputs[1])
	{
		if (is_number(inputs[1]))
		{
			if (inputs[2])
				return (print_error("minishell: too many argument\n", 2));
			g_exit_status = my_atoi(inputs[1]);
			if (g_exit_status > 255)
				g_exit_status = 255;
			else if (g_exit_status < 0)
				g_exit_status = 255;
		}
		else
			print_error("minishell: numeric argument is required\n", 2);
	}
	free_envv(inputs);
	free_envv(s_hell->envv);
	exit(g_exit_status);
}
