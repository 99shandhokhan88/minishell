/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzashev <vzashev@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 01:10:33 by vzashev           #+#    #+#             */
/*   Updated: 2024/05/02 02:29:52 by vzashev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_var_len(char *str)
{
	int	len;

	len = 0;
	while ((is_alpha_or_digit(str[len])) || (str[len] == '_'))
		len++;
	if ((!(len)) && (str[len] == '?'))
		return (1);
	return (len);
}

void	add_escaped_char(char *src, char *dst, int *i, int *j)
{
	dst[(*j)++] = '\\';
	dst[(*j)++] = src[(*i)++];
}

char	*dup_value(char *str)
{
	int		maxlen;
	char	*value;
	int		i;
	int		j;

	maxlen = len_str(str) * 2;
	value = alloc_with_zero(sizeof(char), (maxlen + 1));
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\\' || str[i] == '$' || str[i] == '"'
			|| str[i] == '\'' || str[i] == '>' || str[i] == '<')
			add_escaped_char(str, value, &i, &j);
		else
			value[j++] = str[i++];
	}
	value[j] = '\0';
	return (value);
}

char	*get_value(char *name, t_mini *s_hell)
{
	char	**env;
	int		i;
	int		j;
	int		k;

	env = s_hell->envv;
	i = 0;
	while (env[i])
	{
		j = 0;
		k = 0;
		while ((env[i][j]) && (env[i][j] != '=') && (env[i][j] == name[k]))
		{
			k++;
			j++;
		}
		if ((env[i][j] == '=') && (!(name[k])))
			return (dup_value(&env[i][j + 1]));
		i++;
	}
	return (NULL);
}

void	expander(t_mini *s_hell, char **input_parsed, int *i)
{
	int		len;
	char	*value;
	char	*name;
	char	*new_input;
	char	*temp;

	len = get_var_len(&(input_parsed[0][*i + 1]));
	name = sub_str(*input_parsed, *i + 1, len);
	if ((len == 1) && (input_parsed[0][*i + 1] == '?'))
		value = my_itoa(g_exit_status);
	else if (len)
		value = get_value(name, s_hell);
	else
		value = dup_str("$");
	free(name);
	new_input = sub_str(*input_parsed, 0, *i);
	temp = join_str(new_input, value);
	free(new_input);
	new_input = join_str(temp, &(input_parsed[0][*i + 1 + len]));
	len = len_str(value);
	free(temp);
	free(value);
	free(*input_parsed);
	*input_parsed = new_input;
	*i += len - 1;
}
