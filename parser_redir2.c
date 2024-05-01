/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzashev <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 19:10:25 by vzashev           #+#    #+#             */
/*   Updated: 2024/05/01 19:38:32 by vzashev          ###   ########.fr       */
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

void	redir_to(char *str, int i, char **input, t_data *data)
{
	char	*filename;
	int		fd;
	int		j;

	j = i;
	if (str[j + 1] == ' ')
		j++;
	filename = get_filename(&(str[j + 1]), &j);
	remove_redir_input(input, i, j);
	fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	free(filename);
	if (fd < 0)
	{
		ft_putstr_fd("Error: wrong permissions\n", 2);
		g_exit = 1;
		data->redir = 0;
		return ;
	}
	dup2(fd, 1);
	if (data->fd_out != 1)
		close(data->fd_out);
	data->fd_out = fd;
	parser_redir(input, data);
}

void	redir_to_append(char *str, int i, char **input, t_data *data)
{
	char	*filename;
	int		fd;
	int		j;

	j = i;
	j++;
	if (str[j + 1] == ' ')
		j++;
	filename = get_filename(&(str[j + 1]), &j);
	remove_redir_input(input, i, j);
	fd = open(filename, O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
	free(filename);
	if (fd < 0)
	{
		ft_putstr_fd("Error: wrong permissions\n", 2);
		g_exit = 1;
		data->redir = 0;
		return ;
	}
	dup2(fd, 1);
	if (data->fd_out != 1)
		close(data->fd_out);
	data->fd_out = fd;
	parser_redir(input, data);
}

void	redir_from(char *str, int i, char **input, t_data *data)
{
	char	*filename;
	int		fd;
	int		j;

	j = i;
	if (str[j + 1] == ' ')
		j++;
	filename = get_filename(&(str[j + 1]), &j);
	remove_redir_input(input, i, j);
	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd < 0)
	{
		ft_putstr_fd("Error: Wrong file name or wrong permissions\n", 2);
		g_exit = 1;
		data->redir = 0;
		return ;
	}
	dup2(fd, 0);
	if (data->fd_in != 0)
		close(data->fd_in);
	data->fd_in = fd;
	parser_redir(input, data);
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
	int	fd_out;

	fd_out = open(".tmp.txt", O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd_out == -1)
	{
		perror("Error opening temporary file for writing");
		exit(EXIT_FAILURE);
	}
	return (fd_out);
}

void	write_to_tmp_file(int fd_out, const char *line)
{
	write(fd_out, line, strlen(line));
	write(fd_out, "\n", 1);
}

int	open_tmp_file_for_reading(void)
{
	int	fd_in;

	fd_in = open(".tmp.txt", O_RDONLY);
	if (fd_in == -1)
	{
		perror("Error opening temporary file for reading");
		exit(EXIT_FAILURE);
	}
	return (fd_in);
}

void	here_doc(const char *delimiter)
{
	int		fd_in;
	int		fd_out;
	char	*line;

	fd_out = open_tmp_file_for_writing();
	while (1)
	{
		line = readline("> ");
		if (comp_str_ignore_spaces(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write_to_tmp_file(fd_out, line);
		free(line);
	}
	close(fd_out);
	fd_in = open_tmp_file_for_reading();
	close(fd_in);
}

void	handle_redir(char **input, int i, t_data *data)
{
	char	*str;
	int		fd_in;

	str = *input;
	if (str[i] == '>' && str[i + 1] != '>')
		redir_to(str, i, input, data);
	else if (str[i] == '>' && str[i + 1] == '>')
		redir_to_append(str, i, input, data);
	else if (str[i] == '<' && str[i + 1] != '<')
		redir_from(str, i, input, data);
	else if (str[i] == '<' && str[i + 1] == '<')
	{
		here_doc(&str[i + 2]);
		extract_command_with_args(*input);
		fd_in = open(".tmp.txt", O_RDONLY);
		if (fd_in == -1)
		{
			printf("Error opening temporary file for reading\n");
			return ;
		}
		dup2(fd_in, 0);
		close(fd_in);
		parser_redir(input, data);
	}
}
