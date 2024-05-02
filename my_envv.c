/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_envv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzashev <vzashev@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:29:16 by vzashev           #+#    #+#             */
/*   Updated: 2024/05/02 02:44:42 by vzashev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	g_exit_status = 0;
}


