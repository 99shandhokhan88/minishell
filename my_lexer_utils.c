/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_lexer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzashev <vzashev@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 11:51:36 by vzashev           #+#    #+#             */
/*   Updated: 2024/05/02 23:00:51 by vzashev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Function: len_quote
 * --------------------
 * Calculates the length of a quoted substring.
 *
 * input: A pointer to the input string.
 * i: A pointer to the current index.
 * quote: The quote character.
 */

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

/*
 * Function: len_input
 * --------------------
 * Calculates the length of the input string, considering quotes.
 *
 * input: The input string.
 *
 * Returns: The length of the input string.
 */

int	len_input(char *input)
{
	int		i;
	char	quote;

	i = 0;
	while (*input)
	{
		if ((*input == ' ') && ((*(input + 1) == ' ')
				|| (*(input + 1) == '\0')))
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

/*
 * Function: inside_quotes_copy
 * -----------------------------
 * Copies characters inside quotes from the source to the destination string.
 *
 * src: A pointer to the source string.
 * dst: A pointer to the destination string.
 * quote: The quote character.
 */

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

/*
 * Function: input_copy
 * ---------------------
 * Copies characters from the source to
 * the destination string, considering quotes.
 *
 * dst: The destination string.
 * src: The source string.
 */

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

/*
 * Function: format_input
 * -----------------------
 * Formats the input string by removing redundant spaces and handling quotes.
 *
 * input: The input string to format.
 *
 * Returns: The formatted input string.
 */

char	*format_input(char *input)
{
	int		len;
	char	*cleaned_input;

	while ((*input == ' ') && (*input))
		input++;
	len = len_input(input);
	if (len == -1)
		return (0);
	cleaned_input = alloc_with_zero(((len + 1)), (sizeof(char)));
	if (!(cleaned_input))
	{
		free(cleaned_input);
		exit(EXIT_FAILURE);
	}
	input_copy(cleaned_input, input);
	return (cleaned_input);
}
