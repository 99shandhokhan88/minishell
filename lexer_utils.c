/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzashev <vzashev@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 00:58:57 by vzashev           #+#    #+#             */
/*   Updated: 2024/05/02 02:25:42 by vzashev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	len_quote(char **input, int *i, char quote)
{
	int	slash;

	while ((**input != quote) && (**input))
	{
		slash = 0;
		if ((slash) && (!(slash % 2)))
		{
			(*input)--;
			(*i)--;
		}
		(*i)++;
		(*input)++;
	}
}

int	len_input(char *input)
{
	int		i;
	char	quote;

	i = 0;
	while (*input)
	{
		if ((*input == ' ') && ((*(input + 1) == ' ') || (*(input + 1) == '\0')))
			input++;
		else if ((*input == '"') || (*input == '\''))
		{
			quote = (*(input++));
			len_quote(&input, &i, quote);
			if (!*input)
				return (-1);
			input++;
			i += 2;
		}
		else if (input++)
			i++;
	}
	return (i);
}

void	inside_quotes_copy(char **src, char **dst, char quote)
{
	int	slash;

	while ((**src) != quote)
	{
		slash = 0;
		if ((slash) && (!(slash % 2)))
			(*((*dst)--)) = (*((*src)--));
		(*((*dst)++)) = (*((*src)++));
	}
}

void	input_copy(char *dst, char *src)
{
	char	quote;

	while (*src)
	{
		if ((*src == ' ') && ((*(src + 1) == ' ') || (*(src + 1) == '\0')))
			src++;
		else if ((*src == '"') || (*src == '\''))
		{
			(*(dst++)) = (*src);
			quote = (*(src++));
			inside_quotes_copy(&src, &dst, quote);
			(*(dst++)) = (*(src++));
		}
		else
			(*(dst++)) = (*(src++));
	}
	*dst = '\0';
}

char	*format_input(char *input)
{
	int		len;
	char	*cleaned_input;

	while ((*input == ' ') && (*input))
		input++;
	len = len_input(input);
	if (len == -1)
		return (0);
	cleaned_input = ((char *)malloc(((len + 1)) * (sizeof(char))));
	if (!(cleaned_input))
		exit(EXIT_FAILURE);
	input_copy(cleaned_input, input);
	return (cleaned_input);
}
