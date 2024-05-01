/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_basic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzashev <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:47:33 by vzashev           #+#    #+#             */
/*   Updated: 2024/05/01 18:50:04 by vzashev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	choose_action(char **inputs, t_data *data)
{
	if (!data->redir)
		data->redir = 1;
	if (!ft_strcmp(inputs[0], "echo"))
		handle_echo(inputs);
	else if (!ft_strcmp(inputs[0], "pwd"))
		handle_pwd();
	else if (!ft_strcmp(inputs[0], "cd"))
		handle_cd(inputs, data);
	else if (!ft_strcmp(inputs[0], "env"))
		handle_env(data->env);
	else if (!ft_strcmp(inputs[0], "exit"))
		handle_exit(inputs, data);
	else if (!ft_strcmp(inputs[0], "export"))
		handle_export(inputs, data);
	else if (!ft_strcmp(inputs[0], "unset"))
		handle_unset(inputs, data);
	else
		handle_exec(inputs, data);
}

void	free_inputs(char **inputs)
{
	int	i;

	i = 0;
	while (inputs[i])
	{
		free(inputs[i]);
		i++;
	}
	free(inputs);
}

void	close_reds(t_data *data)
{
	if (data->fd_in != 0)
	{
		close(data->fd_in);
		data->fd_in = 0;
	}
	if (data->fd_out != 1)
	{
		close(data->fd_out);
		data->fd_out = 1;
	}
}

void	exit_pipe(t_data *data)
{
	free_inputs(data->env);
	free(data->pwd);
	exit(EXIT_SUCCESS);
}

void	setup_fds(int oldfd[2])
{
	oldfd[0] = dup(1);
	oldfd[1] = dup(0);
}

void	close_fds(int oldfd[2])
{
	close(oldfd[0]);
	close(oldfd[1]);
}

int	handle_basic(char *clean_input, t_data *data, int piped)
{
	char	**inputs;
	int		oldfd[2];

	if (parser_error(clean_input))
	{
		free(clean_input);
		return (0);
	}
	setup_fds(oldfd);
	clean_input = input_cleaner(clean_input);
	parser_redir(&clean_input, data);
	clean_input = input_cleaner(clean_input);
	inputs = input_split(clean_input);
	if (!inputs)
		exit(EXIT_FAILURE);
	free(clean_input);
	choose_action(inputs, data);
	free_inputs(inputs);
	dup2(oldfd[0], 1);
	dup2(oldfd[1], 0);
	close_reds(data);
	close_fds(oldfd);
	if (piped)
		exit_pipe(data);
	return (0);
}
