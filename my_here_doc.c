/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzashev <vzashev@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 20:10:33 by vzashev           #+#    #+#             */
/*   Updated: 2024/05/02 22:21:21 by vzashev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Function: here_doc
 * -------------------
 * Implements the "here document" functionality,
 * where the user can input multiple lines until a delimiter is entered.
 *
 * delimiter: The delimiter indicating the end of the input.
 */

void	here_doc(const char *delimiter)
{
	int		in;
	int		out;
	char	*line;

	out = open_tmp_file_for_writing();
	while (1)
	{
		line = readline("> ");
		if (comp_str_ignore_spaces(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write_to_tmp_file(out, line);
		free(line);
	}
	close(out);
	in = open_tmp_file_for_reading();
	close(in);
}

/*
 * Function: write_to_tmp_file
 * ----------------------------
 * Writes a line to a temporary file.
 *
 * out: The file descriptor for the temporary file.
 * line: The line to write to the file.
 */

void	write_to_tmp_file(int out, const char *line)
{
	write(out, line, len_str(line));
	write(out, "\n", 1);
}

/*
 * Function: open_tmp_file_for_reading
 * ------------------------------------
 * Opens the temporary file for reading.
 *
 * Returns: The file descriptor for the temporary file.
 */

int	open_tmp_file_for_reading(void)
{
	int	in;

	in = open(".tmp.txt", O_RDONLY);
	if (in == -1)
	{
		perror("Error: not opening temporary file for reading!\n");
		exit(EXIT_FAILURE);
	}
	return (in);
}

/*
 * Function: open_tmp_file_for_writing
 * ------------------------------------
 * Opens the temporary file for writing.
 *
 * Returns: The file descriptor for the temporary file.
 */

int	open_tmp_file_for_writing(void)
{
	int	out;

	out = open(".tmp.txt", O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (out == -1)
	{
		perror("Error: not opening temporary file for writing!\n");
		exit(EXIT_FAILURE);
	}
	return (out);
}

/*
 * Function: extract_command_with_args
 * ------------------------------------
 * Extracts the command with its arguments from the input string.
 *
 * input: The input string containing the command and its arguments.
 */

void	extract_command_with_args(char *input)
{
	int	i;

	i = 0;
	while (input[i] != '\0' && input[i] != '<' && input[i] != '>')
		i++;
	input[i] = '\0';
}
