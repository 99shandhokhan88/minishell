/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzashev <vzashev@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:45:44 by vzashev           #+#    #+#             */
/*   Updated: 2024/05/02 02:42:18 by vzashev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	replace_envv(char *new_var, t_mini *s_hell, int index)
{
	if (str_char(new_var, '='))
	{
		free(s_hell->envv[index]);
		s_hell->envv[index] = dup_str(new_var);
	}
}

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
				return (print_error("export: bad identifier\n", 1));
			i++;
		}
	}
	else
		export_alone(s_hell);
	g_exit_status = 0;
}
