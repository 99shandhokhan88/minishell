/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzashev <vzashev@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:18:39 by vzashev           #+#    #+#             */
/*   Updated: 2024/05/02 18:18:57 by vzashev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Function: my_lexer
 * -------------------
 * Tokenizes and formats the input string for parsing.
 *
 * s_hell: A pointer to the minishell structure.
 * input: The input string to tokenize and format.
 *
 * Returns: 1 if successful, 0 otherwise.
 */

int	my_lexer(t_mini *s_hell, char *input)
{
	char	*formatted_input;

	formatted_input = format_input(input);
	if (formatted_input == NULL)
	{
		printf("Error: this minishell doesn't support multiline!\n");
		return (0);
	}
	if (!(*formatted_input))
	{
		free(formatted_input);
		return (0);
	}
	return (parser(s_hell, formatted_input, 0));
}
