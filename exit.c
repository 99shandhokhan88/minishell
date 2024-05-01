/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzashev <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:44:43 by vzashev           #+#    #+#             */
/*   Updated: 2024/05/01 18:45:19 by vzashev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_sentence(char *str, int status)
{
	g_exit = status;
	ft_putstr_fd(str, 2);
}

int	is_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	handle_exit(char **inputs, t_data *data)
{
	g_exit = 0;
	if (inputs[1])
	{
		if (is_number(inputs[1]))
		{
			if (inputs[2])
				return (error_sentence("\tminishell: too many argument\n", 2));
			g_exit = ft_atoi(inputs[1]);
			if (g_exit > 255)
				g_exit = 255;
			else if (g_exit < 0)
				g_exit = 255;
		}
		else
			error_sentence("\t\tminishell: numeric argument is required\n", 2);
	}
	free_env(inputs);
	free_env(data->env);
	exit(g_exit);
}
