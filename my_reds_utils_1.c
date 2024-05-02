/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_reds_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzashev <vzashev@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 16:09:00 by vzashev           #+#    #+#             */
/*   Updated: 2024/05/02 22:19:09 by vzashev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
   This function handles the input redirection (<)
   in the command line.
   It extracts the filename from the command line,
   opens the file for reading,
   and redirects the standard input to this file descriptor using dup2.
   If the file cannot be opened due to wrong permissions
   or invalid filename,
   it prints an error message and sets the exit status
   to 1.
*/

void	red_in(char *str, int i, char **input, t_mini *s_hell)
{
	char	*filename;
	int		fd;
	int		j;

	j = i;
	if (str[j + 1] == ' ')
		j++;
	filename = get_filename(&(str[j + 1]), &j);
	remove_red_input(input, i, j);
	fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	free(filename);
	if (fd < 0)
	{
		print_str_fd("Error: wrong permissions!\n", 2);
		g_exit = 1;
		s_hell->red = 0;
		return ;
	}
	dup2(fd, 1);
	if (s_hell->out != 1)
		close(s_hell->out);
	s_hell->out = fd;
	my_redirections(input, s_hell);
}

/*
   This function handles the output redirection (>)
   in the command line.
   It extracts the filename from the command line,
   opens the file for writing,
   and redirects the standard output to
   this file descriptor using dup2.
   If the file cannot be opened due to wrong permissions
   or invalid filename,
   it prints an error message and sets the exit status to 1.
*/

void	red_append(char *str, int i, char **input, t_mini *s_hell)
{
	char	*filename;
	int		fd;
	int		j;

	j = i;
	j++;
	if (str[j + 1] == ' ')
		j++;
	filename = get_filename(&(str[j + 1]), &j);
	remove_red_input(input, i, j);
	fd = open(filename, O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
	free(filename);
	if (fd < 0)
	{
		print_str_fd("Error: wrong permissions!\n", 2);
		g_exit = 1;
		s_hell->red = 0;
		return ;
	}
	dup2(fd, 1);
	if (s_hell->out != 1)
		close(s_hell->out);
	s_hell->out = fd;
	my_redirections(input, s_hell);
}

/*
   This function handles the output redirection (>>)
   in the command line.
   It extracts the filename from the command line,
   opens the file for appending,
   and redirects the standard output to
   this file descriptor using dup2.
   If the file cannot be opened due to wrong permissions
   or invalid filename,
   it prints an error message and sets the exit status to 1.
*/

void	red_out(char *str, int i, char **input, t_mini *s_hell)
{
	char	*filename;
	int		fd;
	int		j;

	j = i;
	if (str[j + 1] == ' ')
		j++;
	filename = get_filename(&(str[j + 1]), &j);
	remove_red_input(input, i, j);
	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd < 0)
	{
		print_str_fd("Error: wrong file name and/or wrong permissions!\n", 2);
		g_exit = 1;
		s_hell->red = 0;
		return ;
	}
	dup2(fd, 0);
	if (s_hell->in != 0)
		close(s_hell->in);
	s_hell->in = fd;
	my_redirections(input, s_hell);
}

/*
   This function compares two strings while
   ignoring leading spaces.
   It returns 0 if the strings are equal,
   -1 if the first string is less than the second,
   and 1 if the first string is greater than the second.
*/

int	comp_str_ignore_spaces(const char *str1, const char *str2)
{
	if (str1 == NULL || str2 == NULL)
	{
		if (str1 == NULL && str2 == NULL)
			return (0);
		else if (str1 == NULL)
			return (-1);
		else
			return (1);
	}
	while (*str2 == ' ')
		str2++;
	return (*str1 - *str2);
}

/*
   This function creates a filename by
   copying characters from the source string to the destination string.
   It stops copying when encountering space, pipe,
   semicolon, redirection symbols, or null terminator.
   Special handling is provided for
   characters enclosed in single or double quotes.
*/

void	make_filename(char *src, char *dst, int i, int k)
{
	while (src[i] != ' ' && src[i] != '|' && src[i] != ';' && src[i] != '>'
		&& src[i] != '<' && src[i])
	{
		if (src[i] == '\'')
		{
			while (src[++i] != '\'')
				dst[k++] = src[i];
			i++;
		}
		else if (src[i] == '"')
		{
			while (src[++i] != '"')
			{
				if (src[i] == '\\')
					i++;
				dst[k++] = src[i];
			}
			i++;
		}
		else
			dst[k++] = src[i++];
	}
	dst[k] = '\0';
}
