
#include "minishell.h"

int	parser_pipe(char *input, int pipe_pos, t_data *data)
{
	char	*new_input;
	int		space;

	space = 0;
	if (input[pipe_pos - 1] == ' ')
		space = 1;
	new_input = ft_strdup(&input[pipe_pos + 1]);
	input[pipe_pos - space] = '\0';
	return (handle_pipe(input, new_input, data));
}

/*
static int	parser_semi(char *input, int semi_pos, t_data *data)
{
	char	*new_input;
	int		space;

	space = 0;
	if (input[semi_pos - 1] == ' ')
		space = 1;
	new_input = ft_strdup(&input[semi_pos + 1]);
	input[semi_pos - space] = '\0';
	handle_basic(input, data, 0);
	if (g_status != 130)
		return (parser_start(new_input, data));
	else
		free(new_input);
	return (0);
}

*/

int			check_special(char **input, int *i, t_data *data)
{
	if ((*input)[*i] == '|')
	{
		parser_pipe((*input), *i, data);
		return (1);
	}
	if ((*input)[*i] == '$')
		parser_variable(input, i, data);
	if ((*input)[*i] == '\'')
	{
		(*i)++;
		//while ((*input)[*i] != '\'')
		//	(*i)++;
	}
	//else if ((*input)[*i] == ';')
	//{
	//	parser_semi((*input), *i, data);
	//	return (1);
	//}
	(*i)++;
	return (0);
}

int			parser_delegator(char *input, t_data *data, int piped)
{
	int		i;
	int		slash_count;
	//int	flag = 0;

	i = 0;
	while (input[i])
	{
		if (input[i] == '"' || input[i] == '\'')
		{
			i++;
			//flag = 1;
			while (input[i] != '"' && input[i] != '\'')
			{
				slash_count = 0;
				//while (input[i] == '\\' && ++i)
				//	slash_count++;
				if (input[i] == '$' && !(slash_count % 2))
					parser_variable(&input, &i, data);
				if (slash_count && !(slash_count % 2))
					i--;
				i++;
			}
		}
		if (check_special(&input, &i, data))
			return (0);
	}
	return (handle_basic(input, data, piped));
}
