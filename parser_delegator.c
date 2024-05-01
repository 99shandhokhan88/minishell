/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_delegator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzashev <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:57:05 by vzashev           #+#    #+#             */
/*   Updated: 2024/05/01 18:58:49 by vzashev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parser_pipe(char *input, int pipe_pos, t_data *data)
{
	char	*new_input;
	int		space;

	space = 0;
	if (input[pipe_pos - 1] == ' ')
		space = 1;
	new_input = ft_strdup(&input[pipe_pos + 1]);
	input[pipe_pos - space] = '\0';
	return (handle_pipe(input, new_input, data));
}

int	check_special(char **input, int *i, t_data *data)
{
	if ((*input)[*i] == '|')
	{
		parser_pipe((*input), *i, data);
		return (1);
	}
	if ((*input)[*i] == '$')
		parser_variable(input, i, data);
	if ((*input)[*i] == '\'')
	{
		(*i)++;
	}
	(*i)++;
	return (0);
}

int	parser_delegator(char *input, t_data *data, int piped)
{
	int		i;
	int		slash_count;

	i = 0;
	while (input[i])
	{
		if (input[i] == '"' || input[i] == '\'')
		{
			i++;
			while (input[i] != '"' && input[i] != '\'')
			{
				slash_count = 0;
				if (input[i] == '$' && !(slash_count % 2)
					&& (input[i - 1] != '\''))
					parser_variable(&input, &i, data);
				if (slash_count && !(slash_count % 2))
					i--;
				i++;
			}
		}
		if (check_special(&input, &i, data))
			return (0);
	}
	return (handle_basic(input, data, piped));
}
