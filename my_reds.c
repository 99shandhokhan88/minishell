/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_reds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzashev <vzashev@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:02:14 by vzashev           #+#    #+#             */
/*   Updated: 2024/05/03 13:42:20 by vzashev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
   This function extracts the filename from
   a redirection command string and returns it.
   It calculates the length of the filename using the get_name_len function,
   allocates memory for the filename,
   and copies characters from the input string
   to the filename while handling special cases
   for characters enclosed in quotes.
   The function returns the extracted filename.
*/

char	*get_filename(char *str, int *j)
{
	int		i;
	int		k;
	char	*filename;

	i = get_name_len(str);
	*j += i;
	filename = malloc((i + 1) * sizeof(char));
	if (!filename)
		return (NULL);
	i = 0;
	k = 0;
	make_filename(str, filename, i, k);
	return (filename);
}

/*
   This function removes the redirection command
   and filename from the input string
   after the redirection operation has been processed.
   It creates a new string by concatenating
   the parts before and after the redirection,
   and updates the input string pointer to point to this new string.
*/

void	remove_red_input(char **input_address, int i, int j)
{
	char	*tmp;
	char	*new_input;

	tmp = sub_str(input_address[0], 0, i);
	new_input = join_str(tmp, &(input_address[0][j + 1]));
	free(tmp);
	*input_address = copy_str(*input_address, new_input);
	if (new_input != NULL)
		free(new_input);
}

/*
   This function handles characters within quotes
   in the input string.
   It skips characters until it
   reaches the closing quote, handling escaped characters.
*/

void	reds_in_quotes(char *str, int *i, char quote)
{
	int	slash;

	while (str[*i] != quote)
	{
		slash = 0;
		if ((slash) && (!(slash % 2)))
			(*i)--;
		(*i)++;
	}
}

/*
   This function identifies and handles redirection
   operations in the parsed input string.
   It iterates through the input string,
   checking for redirection symbols ('>' or '<').
   When a redirection symbol is found,
   it calls the appropriate function to handle the redirection.
   If a here-document redirection ('<<') is encountered,
   it initiates the here-document process.
   The function returns 1
   if redirections were found and processed, 0 otherwise.
*/

void	handle_reds(char **input, int i, t_mini *s_hell)
{
	char	*str;
	int		in;

	str = *input;
	if (str[i] == '>' && str[i + 1] != '>')
		red_in(str, i, input, s_hell);
	else if (str[i] == '>' && str[i + 1] == '>')
		red_append(str, i, input, s_hell);
	else if (str[i] == '<' && str[i + 1] != '<')
		red_out(str, i, input, s_hell);
	else if (str[i] == '<' && str[i + 1] == '<')
	{
		here_doc(&str[i + 2]);
		extract_command_with_args(*input);
		in = open(".tmp.txt", O_RDONLY);
		if (in == -1)
		{
			printf("minishell: not opening temporary file for reading\n");
			return ;
		}
		dup2(in, 0);
		close(in);
		my_redirections(input, s_hell);
	}
}

/*
   This function is the main entry point for
   handling redirections.
   It iterates through the parsed input string,
   searching for redirection symbols.
   When a redirection symbol is found,
   it delegates the handling to the handle_reds function.
   If redirections are found and processed,
   the function returns 1; otherwise, it returns 0.
*/

int	my_redirections(char **parsed_input, t_mini *s_hell)
{
	int		i;
	char	quote;

	i = -1;
	while ((*parsed_input)[++i])
	{
		if (((*parsed_input)[i] == '\'') || ((*parsed_input)[i] == '"'))
		{
			quote = ((*parsed_input)[i]);
			i++;
			reds_in_quotes((*parsed_input), &i, quote);
		}
		if (((*parsed_input)[i] == '>') || ((*parsed_input)[i] == '<'))
		{
			handle_reds(parsed_input, i, s_hell);
			return (1);
		}
	}
	return (0);
}
