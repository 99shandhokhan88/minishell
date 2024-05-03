/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzashev <vzashev@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 10:31:48 by vzashev           #+#    #+#             */
/*   Updated: 2024/05/03 15:20:49 by vzashev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Parser function responsible for processing
 * the input from the lexer and executing commands
 * accordingly.
 *
 * It iterates through the input string,
 * handling quotes, expansions, and checking for pipes or dollar signs.
 * Calls the my_brain function to execute
 * the parsed commands.
*/

int	parser(t_mini *s_hell, char *lexer_input, int pipe)
{
	int		i;
	int		slash;

	i = 0;
	slash = 0;
	while (lexer_input[i])
	{
		if ((lexer_input[i] == '"') || (lexer_input[i] == '\''))
		{
			i++;
			while ((lexer_input[i] != '"') && (lexer_input[i] != '\''))
			{
				slash = 0;
				if ((lexer_input[i] == '$') && (!(slash % 2))
					&& ((lexer_input[i - 1] != '\'')))
					expander(s_hell, &lexer_input, &i);
				if (slash && !(slash % 2))
					i--;
				i++;
			}
		}
		if (check_pipe_or_dollar(&lexer_input, &i, s_hell))
			return (0);
	}
	return (my_brain(lexer_input, s_hell, pipe));
}
