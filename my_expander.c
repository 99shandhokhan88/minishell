/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzashev <vzashev@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:23:29 by vzashev           #+#    #+#             */
/*   Updated: 2024/05/03 19:47:21 by vzashev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Function: escape
 * ----------------
 * Escapes special characters in the input string
 * and copies them to the destination string.
 *
 * src: The source string containing characters to escape.
 * dst: The destination string to copy the escaped characters.
 * i: A pointer to the current index in the source string.
 * j: A pointer to the current index in the destination string.
 */

void	escape(char *src, char *dst, int *i, int *j)
{
	dst[(*j)++] = '\\';
	dst[(*j)++] = src[(*i)++];
}

/*
 * Function: dup_value
 * -------------------
 * Duplicates a string,
 * escaping special characters during the duplication process.
 *
 * str: The string to duplicate.
 *
 * Returns: A pointer to the duplicated string with escaped characters.
 */

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
			escape(str, value, &i, &j);
		else
			value[j++] = str[i++];
	}
	value[j] = '\0';
	return (value);
}

/*
 * Function: get_var_len
 * ----------------------
 * Computes the length of an environment variable name in the input string.
 *
 * str: The input string containing the environment variable name.
 *
 * Returns: The length of the environment variable name.
 */

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

/*
 * Function: get_value
 * --------------------
 * Retrieves the value of
 * an environment variable from the shell's environment variables.
 *
 * name: The name of the environment variable to retrieve.
 * s_hell: A pointer to the shell structure.
 *
 * Returns: A pointer to the value of
 * the environment variable, or NULL if not found.
 */

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
	return ("\n");
}

/*
 * Function: expander
 * -------------------
 * Expands environment variables
 * and escapes characters in the input string.
 *
 * s_hell: A pointer to the shell structure.
 * input_parsed: A pointer to the parsed input string.
 * i: A pointer to the current index in the input string.
 */

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
		value = my_itoa(g_exit);
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
	free(value);
	free(temp);
	free(*input_parsed);
	*input_parsed = new_input;
	*i += len - 1;
}
