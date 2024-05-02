/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_envv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzashev <vzashev@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 08:50:10 by vzashev           #+#    #+#             */
/*   Updated: 2024/05/02 22:18:46 by vzashev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Function: init_envv
 * --------------------
 * Initializes the shell environment variables from the given array.
 *
 * envv: An array containing environment variable strings.
 * s_hell: A pointer to the shell structure.
 *
 * Returns: 0 on success, 1 on failure.
 */

int	init_envv(char *envv[], t_mini *s_hell)
{
	int	i;

	i = 0;
	while (envv && envv[i])
		i++;
	s_hell->envv = alloc_with_zero(sizeof(char *), (i + 1));
	if (!s_hell->envv)
		return (0);
	i = 0;
	while (envv && envv[0] && envv[i])
	{
		s_hell->envv[i] = dup_str(envv[i]);
		i++;
	}
	s_hell->envv[i] = NULL;
	return (0);
}

/*
 * Function: dup_env
 * ------------------
 * Duplicates the environment variable array.
 *
 * envv: An array containing environment variable strings.
 *
 * Returns: A duplicate of the environment variable array.
 */

char	**dup_env(char **envv)
{
	char	**s_hell_envv;
	int		i;

	i = 0;
	s_hell_envv = alloc_with_zero(sizeof(char *), len_envv(envv));
	if (!s_hell_envv)
		exit(EXIT_FAILURE);
	while (envv[i])
	{
		s_hell_envv[i] = dup_str(envv[i]);
		i++;
	}
	s_hell_envv[i] = 0;
	return (s_hell_envv);
}

/*
 * Function: my_envv
 * -------------------
 * Displays the current environment variables.
 *
 * envv: An array containing environment variable strings.
 */

void	my_envv(char **envv)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (envv[i])
	{
		str = str_str(envv[i], "=");
		if (str)
		{
			j = 0;
			while (envv[i][j])
			{
				write(1, &envv[i][j], 1);
				j++;
			}
			write(1, "\n", 1);
		}
		i++;
	}
	g_exit = 0;
}
