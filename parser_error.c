/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzashev <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:59:11 by vzashev           #+#    #+#             */
/*   Updated: 2024/05/01 19:00:23 by vzashev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_redir(char *str, int *i, char c)
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

void	skip_quotes(char *str, int *i)
{
	char	quote;

	quote = str[(*i)++];
	while (str[(*i)] != quote)
		(*i)++;
}

int	parser_error(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			skip_quotes(str, &i);
		if (str[i] == '>' || str[i] == '<')
		{
			if (error_redir(str, &i, str[i]))
			{
				g_exit = 1;
				printf("Error: wrong or unsupported redirection\n");
				return (1);
			}
		}
		else
			i++;
	}
	return (0);
}
