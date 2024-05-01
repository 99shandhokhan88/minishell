/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzashev <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 19:12:25 by vzashev           #+#    #+#             */
/*   Updated: 2024/05/01 19:15:05 by vzashev          ###   ########.fr       */
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

void	remove_redir_input(char **input_address, int i, int j)
{
	char	*tmp;
	char	*new_input;

	tmp = ft_substr(input_address[0], 0, i);
	new_input = ft_strjoin(tmp, &(input_address[0][j + 1]));
	free(tmp);
	*input_address = strcpy(*input_address, new_input);
	if (new_input != NULL)
		free(new_input);
}

void	parser_redir_quotes(char *str, int *i, char quote)
{
	int	slash_count;

	while (str[*i] != quote)
	{
		slash_count = 0;
		if (slash_count && !(slash_count % 2))
			(*i)--;
		(*i)++;
	}
}

int	parser_redir(char **input_address, t_data *data)
{
	int		i;
	char	quote;

	i = -1;
	while ((*input_address)[++i])
	{
		if ((*input_address)[i] == '\'' || (*input_address)[i] == '"')
		{
			quote = (*input_address)[i];
			i++;
			parser_redir_quotes((*input_address), &i, quote);
		}
		if ((*input_address)[i] == '>' || (*input_address)[i] == '<')
		{
			handle_redir(input_address, i, data);
			return (1);
		}
	}
	return (0);
}
