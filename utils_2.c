/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzashev <vzashev@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:36:35 by vzashev           #+#    #+#             */
/*   Updated: 2024/05/03 16:31:22 by vzashev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	s_hell_init(t_mini *s_hell)
{
	s_hell->in = 0;
	s_hell->out = 1;
	s_hell->red = 1;
}

size_t	custom_strspn(const char *str, const char *accept)
{
	const char	*space;
	const char	*letter;
	size_t		count;

	space = str;
	letter = accept;
	count = 0;
	while (*space)
	{
		while (*letter)
		{
			if (*space == *letter)
			{
				++count;
				break ;
			}
			++letter;
		}
		++space;
		if (!*letter)
			return (count);
	}
	return (count);
}

void	free_shell(t_mini *s_hell)
{
	int	i;

	i = 0;
	if (!s_hell->envv)
		return ;
	while (s_hell->envv[i])
	{
		free(s_hell->envv[i]);
		i++;
	}
	free(s_hell->envv);
}

int	check_pipe_at_beginning(char *input)
{
	if (input == NULL || input[0] == '\0')
		return (0);
	if (input[0] == '|')
	{
		printf("minishell: wrong syntax\n");
		return (1);
	}
	return (0);
}

int	is_digit(int n)
{
	return (n >= '0' && n <= '9');
}
