/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_reds_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzashev <vzashev@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 20:14:11 by vzashev           #+#    #+#             */
/*   Updated: 2024/05/02 18:18:53 by vzashev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
   This function calculates the length of
   a name in a redirection command.
   It iterates through the characters of
   the input string until it encounters
   space, pipe, semicolon, or redirection symbols,
   or reaches the end of the string.
   It handles special cases for characters enclosed
   in single or double quotes,
   skipping over them while counting the length.
   The function returns the length of the name.
*/

int	get_name_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] != ' ' && str[i] != '|' && str[i] != ';' && str[i] != '>'
		&& str[i] != '<' && str[i])
	{
		if (str[i] == '\'')
		{
			while (str[++i] != '\'')
				;
			i++;
		}
		else if (str[i] == '"')
		{
			while (str[++i] != '"')
			{
				if (str[i] == '\\')
					i++;
			}
			i++;
		}
		else
			i++;
	}
	return (i);
}
