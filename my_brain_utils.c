/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_brain_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzashev <vzashev@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:00:18 by vzashev           #+#    #+#             */
/*   Updated: 2024/05/03 13:38:06 by vzashev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Function: skip_quotes
 * ----------------------
 * Skips characters enclosed in quotes within the input string.
 *
 * input: The input string to be parsed.
 * pos: A pointer to the current position within the string.
 */

void	skip_quotes(char *input, int *pos)
{
	char	quote;

	quote = (input[(*pos)++]);
	while ((input[(*pos)]) != quote)
		(*pos)++;
}

/*
 * Function: check_reds
 * ---------------------
 * Checks if consecutive characters in the string represent redirection symbols.
 *
 * str: The string to be checked.
 * i: A pointer to the current position within the string.
 * c: The redirection symbol to be checked ('>' or '<').
 *
 * Returns: 1 if the redirection is invalid, 0 otherwise.
 */

int	check_reds(char *str, int *i, char c)
{
	int	count;

	count = 0;
	while (str[(*i)] == c)
	{
		count++;
		(*i)++;
	}
	if ((c == '>' && count > 2) || (c == '<' && count > 2))
		return (1);
	while (str[(*i)] == ' ')
		(*i)++;
	if (!str[(*i)])
		return (1);
	return (0);
}

/*
 * Function: my_error
 * -------------------
 * Checks for errors in the input command, such as unsupported redirections.
 *
 * input: The input command string.
 *
 * Returns: 1 if an error is found, 0 otherwise.
 */

int	my_error(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if ((input[i] == '"') || (input[i] == '\''))
			skip_quotes(input, &i);
		if ((input[i] == '>') || (input[i] == '<'))
		{
			if (check_reds(input, &i, input[i]))
			{
				g_exit = 1;
				printf("minishell$: error: wrong redirection\n");
				return (1);
			}
		}
		else
			i++;
	}
	return (0);
}

/*
 * Function: free_inputs
 * ----------------------
 * Frees memory allocated for the input array.
 *
 * inputs: The array of input strings to be freed.
 */

void	free_inputs(char **inputs)
{
	int	i;

	i = 0;
	while (inputs[i])
	{
		free(inputs[i]);
		i++;
	}
	free(inputs);
}
