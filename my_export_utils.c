/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzashev <vzashev@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:46:15 by vzashev           #+#    #+#             */
/*   Updated: 2024/05/02 03:08:06 by vzashev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_envv(char **envv)
{
	int	i;

	i = 0;
	while (envv[i])
		i++;
	return (++i);
}

void	free_envv(char **envv)
{
	int	i;
	int	envv_len;

	i = 0;
	envv_len = len_envv(envv);
	while (i < envv_len)
		free(envv[i++]);
	free(envv);
}

int	export_printer(char **envv)
{
	int	i;
	int	j;
	int	equal;

	i = -1;
	while (envv[++i])
	{
		equal = 1;
		j = 0;
		write(1, "declare -x ", 11);
		while (envv[i][j])
		{
			if (envv[i][j] == '\\' || envv[i][j] == '$'
				|| envv[i][j] == '\"')
				write(1, "\\", 1);
			write(1, &envv[i][j], 1);
			if (envv[i][j] == '=' && equal-- == 1)
				write(1, "\"", 1);
			j++;
		}
		if (equal != 1)
			write(1, "\"", 1);
		write(1, "\n", 1);
	}
	return (1);
}

void	export_alone(t_mini *s_hell)
{
	int		i;
	int		j;
	char	**temp_envv;
	char	*swap;

	i = 0;
	temp_envv = dup_env(s_hell->envv);
	while (temp_envv[i + 1])
	{
		j = i + 1;
		if (strcmp(temp_envv[i], temp_envv[j]) > 0)
		{
			swap = temp_envv[j];
			temp_envv[j] = temp_envv[i];
			temp_envv[i] = swap;
			i = 0;
		}
		else
			i++;
	}
	export_printer(temp_envv);
	free_envv(temp_envv);
}
