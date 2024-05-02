/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzashev <vzashev@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 01:09:25 by vzashev           #+#    #+#             */
/*   Updated: 2024/05/02 01:20:26 by vzashev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_pars(char *input, int pipe_pos, t_mini *s_hell)
{
	char	*new_input;
	int		space;

	space = 0;
	if (input[pipe_pos - 1] == ' ')
		space = 1;
	new_input = dup_str(&input[pipe_pos + 1]);
	input[pipe_pos - space] = '\0';
	return (my_pipe(input, new_input, s_hell));
}

int	check_pipe_or_dollar(char **input, int *i, t_mini *s_hell)
{
	if ((*input)[*i] == '|')
	{
		pipe_pars((*input), *i, s_hell);
		return (1);
	}
	if ((*input)[*i] == '$')
		expander(s_hell, input, i);
	if ((*input)[*i] == '\'')
	{
		(*i)++;
	}
	(*i)++;
	return (0);
}

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
