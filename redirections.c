/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_red.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzashev <vzashev@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 19:12:25 by vzashev           #+#    #+#             */
/*   Updated: 2024/05/02 00:18:01 by vzashev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	remove_red_input(char **input_address, int i, int j)
{
	char	*tmp;
	char	*new_input;

	tmp = sub_str(input_address[0], 0, i);
	new_input = join_str(tmp, &(input_address[0][j + 1]));
	free(tmp);
	*input_address = strcpy(*input_address, new_input);
	if (new_input != NULL)
		free(new_input);
}












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
			printf("Error opening temporary file for reading\n");
			return ;
		}
		dup2(in, 0);
		close(in);
		my_redirections(input, s_hell);
	}
}

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
