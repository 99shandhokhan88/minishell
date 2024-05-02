/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_brain_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzashev <vzashev@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:59:11 by vzashev           #+#    #+#             */
/*   Updated: 2024/05/02 02:31:32 by vzashev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_quotes(char *input, int *pos)
{
	char	quote;

	quote = (input[(*pos)++]);
	while ((input[(*pos)]) != quote)
		(*pos)++;
}

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
				g_exit_status = 1;
				printf("Error: wrong or unsupported redection\n");
				return (1);
			}
		}
		else
			i++;
	}
	return (0);
}
