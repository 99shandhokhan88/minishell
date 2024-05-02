/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzashev <vzashev@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 19:22:47 by vzashev           #+#    #+#             */
/*   Updated: 2024/05/02 02:42:21 by vzashev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			return (print_error("unset: invalid identifier\n", 1));
	}
}
