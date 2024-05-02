/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzashev <vzashev@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:02:58 by vzashev           #+#    #+#             */
/*   Updated: 2024/05/02 18:18:49 by vzashev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*next_input(char *str)
{
	char	quote;
	int		slash;

	str--;
	while (*(++str))
	{
		if ((*str == '"') || (*str == '\''))
		{
			quote = *(str++);
			while (*str != quote)
			{
				slash = 0;
				if (slash && !(slash % 2))
					str--;
				str++;
			}
		}
		if (*str == ' ')
			return (str + 1);
	}
	return (str);
}

size_t	words_count(char *str)
{
	int		i;
	char	quote;
	int		slash;

	i = 1;
	str--;
	while (*(++str))
	{
		if ((*str == '"') || (*str == '\''))
		{
			quote = *(str++);
			while (*str != quote)
			{
				slash = 0;
				if (slash && !(slash % 2))
					str--;
				str++;
			}
		}
		if (*str == ' ')
			i++;
	}
	return (i);
}

void	copy_new_split(char *src, char *dst, char quote)
{
	while (*src != ' ' && *src)
	{
		if (*src == '\'')
		{
			quote = *(src++);
			while (*src != quote)
				*(dst++) = *(src++);
			src++;
		}
		else if (*src == '"')
		{
			quote = *(src++);
			while (*src != quote)
				*(dst++) = *(src++);
			src++;
		}
		else
			*(dst++) = *(src++);
	}
	*dst = '\0';
}

char	*create_split(char *src)
{
	int		len;
	char	*dst;
	char	quote;

	quote = 0;
	len = len_str(src);
	dst = malloc((len + 1) * sizeof(char));
	if (!dst)
		exit(EXIT_FAILURE);
	copy_new_split(src, dst, quote);
	return (dst);
}

char	**split_input(char *str)
{
	char	**inputs;
	size_t	count;
	size_t	i;

	count = words_count(str);
	inputs = malloc((count + 1) * sizeof(char *));
	if (!inputs)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < count)
	{
		inputs[i++] = create_split(str);
		if (i > 0 && !inputs[i - 1])
			return (NULL);
		str = next_input(str);
	}
	inputs[i] = NULL;
	return (inputs);
}
