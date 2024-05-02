/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_red2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzashev <vzashev@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 19:10:25 by vzashev           #+#    #+#             */
/*   Updated: 2024/05/02 00:21:02 by vzashev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		print_str_fd("Error: wrong permissions\n", 2);
		g_exit_status = 1;
		s_hell->red = 0;
		return ;
	}
	dup2(fd, 1);
	if (s_hell->out != 1)
		close(s_hell->out);
	s_hell->out = fd;
	my_redirections(input, s_hell);
}

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
		print_str_fd("Error: wrong permissions\n", 2);
		g_exit_status = 1;
		s_hell->red = 0;
		return ;
	}
	dup2(fd, 1);
	if (s_hell->out != 1)
		close(s_hell->out);
	s_hell->out = fd;
	my_redirections(input, s_hell);
}

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
		print_str_fd("Error: Wrong file name or wrong permissions\n", 2);
		g_exit_status = 1;
		s_hell->red = 0;
		return ;
	}
	dup2(fd, 0);
	if (s_hell->in != 0)
		close(s_hell->in);
	s_hell->in = fd;
	my_redirections(input, s_hell);
}

void	extract_command_with_args(char *input)
{
	int	i;

	i = 0;
	while (input[i] != '\0' && input[i] != '<' && input[i] != '>')
		i++;
	input[i] = '\0';
}

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

int	open_tmp_file_for_writing(void)
{
	int	out;

	out = open(".tmp.txt", O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (out == -1)
	{
		perror("Error opening temporary file for writing");
		exit(EXIT_FAILURE);
	}
	return (out);
}

void	write_to_tmp_file(int out, const char *line)
{
	write(out, line, strlen(line));
	write(out, "\n", 1);
}

int	open_tmp_file_for_reading(void)
{
	int	in;

	in = open(".tmp.txt", O_RDONLY);
	if (in == -1)
	{
		perror("Error opening temporary file for reading");
		exit(EXIT_FAILURE);
	}
	return (in);
}

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

