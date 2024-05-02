/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzashev <vzashev@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:54:49 by vzashev           #+#    #+#             */
/*   Updated: 2024/05/02 01:08:36 by vzashev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lexer(t_mini *s_hell, char *input)
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
