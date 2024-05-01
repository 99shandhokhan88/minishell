/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzashev <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 19:23:13 by vzashev           #+#    #+#             */
/*   Updated: 2024/05/01 19:23:17 by vzashev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	check_pipe_at_beginning(char *input)
{
	if (input == NULL || input[0] == '\0')
		return (0);
	if (input[0] == '|')
	{
		printf("Error: Wrong syntax.\n");
		return (1);
	}
	return (0);
}

void	free_shell(t_data *s_hell)
{
	int	i;

	i = 0;
	if (!s_hell->env)
		return ;
	while (s_hell->env[i])
	{
		free(s_hell->env[i]);
		i++;
	}
	free(s_hell->env);
}

size_t	len_str(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	*set_to_zero(void *space, int zero, size_t dimension)
{
	unsigned char	*temp;
	size_t			i;

	temp = (unsigned char *)space;
	i = 0;
	while (i < dimension)
		temp[i++] = zero;
	return (space);
}

void	*alloc_with_zero(size_t type_count, size_t size)
{
	void	*res;
	int		len;

	if (type_count == SIZE_MAX || size == SIZE_MAX)
		return (NULL);
	len = type_count * size;
	res = (void *) malloc(len);
	if (res == NULL)
		return (NULL);
	set_to_zero(res, '\0', len);
	return (res);
}
