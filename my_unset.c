/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzashev <vzashev@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 15:12:18 by vzashev           #+#    #+#             */
/*   Updated: 2024/05/02 18:50:20 by vzashev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
   This function removes the specified environment variable
   from the environment array.
   It creates a new environment array
   with one less element, copies all elements except
   the one to be removed from the old array
   to the new one, and frees the memory of the old array.
   The function returns the new environment array.
*/

char	**unset_envv(char **old_env, int index)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	j = 0;
	new_env = malloc(sizeof(char *) * (len_envv(old_env) - 1));
	if (!new_env)
		exit(EXIT_FAILURE);
	while (old_env[i])
	{
		if (i != index)
		{
			new_env[j] = dup_str(old_env[i]);
			j++;
		}
		i++;
	}
	free_envv(old_env);
	i--;
	new_env[i] = NULL;
	return (new_env);
}

/*
   This function is responsible for unsetting
   environment variables specified in the inputs array.
   It iterates through the inputs array,
   checks if each input is a valid environment variable identifier,
   finds the index of the corresponding
   environment variable in the environment array,
   and removes it
   using the unset_envv function.
*/

void	my_unset(char **inputs, t_mini *s_hell)
{
	int	i;
	int	index;

	i = 1;
	while (inputs[i])
	{
		if (check_export(inputs[i]))
		{
			index = envv_index(inputs[i], s_hell);
			if (index > 0)
				s_hell->envv = unset_envv(s_hell->envv, index);
			i++;
		}
		else
			return (print_error("Error: unset: invalid identifier!\n", 1));
	}
}
