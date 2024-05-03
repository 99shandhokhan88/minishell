/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzashev <vzashev@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 23:01:59 by vzashev           #+#    #+#             */
/*   Updated: 2024/05/03 13:41:18 by vzashev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Function: envv_index
 * ---------------------
 * Finds the index of an environment variable
 * in the shell's environment variable array.
 *
 * name: The name of the environment variable to find.
 * s_hell: A pointer to the shell structure containing
 * the environment variable array.
 *
 * Returns: The index of the environment variable
 * if found, otherwise -1.
 */

int	envv_index(char *name, t_mini *s_hell)
{
	int		y;
	int		x;

	x = 0;
	while (s_hell->envv[x])
	{
		y = 0;
		while (s_hell->envv[x][y] && s_hell->envv[x][y] == name[y]
		&& name[y] != '\0' && name[y] != '=' &&
		s_hell->envv[x][y] != '\0' && s_hell->envv[x][y] != '=')
			y++;
		if ((s_hell->envv[x][y] == '\0' || s_hell->envv[x][y] == '=') &&
		(name[y] == '\0' || name[y] == '='))
			return (x);
		x++;
	}
	return (-1);
}

/*
 * Function: check_export
 * -----------------------
 * Checks if a string is a valid export format.
 *
 * str: The string to check.
 *
 * Returns: 1 if the string is a valid export format, 0 otherwise.
 */

int	check_export(char *str)
{
	int	i;

	i = 0;
	if (is_digit(str[i]))
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!is_alpha_or_digit(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

/*
 * Function: replace_envv
 * -----------------------
 * Replaces an environment variable with a new value.
 *
 * new_var: The new value to set for the environment variable.
 * s_hell: A pointer to the shell structure
 * containing the environment variable array.
 * index: The index of the environment variable to replace.
 */

void	replace_envv(char *new_var, t_mini *s_hell, int index)
{
	if (str_char(new_var, '='))
	{
		free(s_hell->envv[index]);
		s_hell->envv[index] = dup_str(new_var);
	}
}

/*
 * Function: export_envv
 * ----------------------
 * Creates a new environment variable array with an additional variable.
 *
 * old_envv: The original environment variable array.
 * export: The new environment variable to add.
 *
 * Returns: The new environment variable array.
 */

char	**export_envv(char **old_envv, char *export)
{
	int		i;
	char	**new_envv;

	i = 0;
	new_envv = malloc(sizeof(char *) * (len_envv(old_envv) + 1));
	if (!new_envv)
		exit(EXIT_FAILURE);
	while (old_envv[i])
	{
		new_envv[i] = dup_str(old_envv[i]);
		i++;
	}
	free_envv(old_envv);
	new_envv[i] = dup_str(export);
	i++;
	new_envv[i] = NULL;
	return (new_envv);
}

/*
 * Function: my_export
 * --------------------
 * Handles the export command,
 * either replacing existing environment variables or adding new ones.
 *
 * inputs: The arguments passed to the export command.
 * s_hell: A pointer to the shell structure containing
 * the environment variable array.
 */

void	my_export(char **inputs, t_mini *s_hell)
{
	int	i;
	int	index;

	i = 1;
	if (inputs[i])
	{
		while (inputs[i])
		{
			index = envv_index(inputs[i], s_hell);
			if (index >= 0 && check_export(inputs[i]))
				replace_envv(inputs[i], s_hell, index);
			else if (check_export(inputs[i]))
			{
				s_hell->envv = export_envv(s_hell->envv, inputs[i]);
				if (!s_hell->envv)
					exit(EXIT_FAILURE);
			}
			else
				return (print_error("minishell$: export: bad identifier\n", 1));
			i++;
		}
	}
	else
		export_alone(s_hell);
	g_exit = 0;
}
