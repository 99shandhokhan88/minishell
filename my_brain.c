/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_brain.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzashev <vzashev@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:47:33 by vzashev           #+#    #+#             */
/*   Updated: 2024/05/02 02:34:41 by vzashev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_fds(int newfd[2])
{
	newfd[0] = dup(1);
	newfd[1] = dup(0);
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

void	close_reds(t_mini *s_hell)
{
	if (s_hell->in != 0)
	{
		close(s_hell->in);
		s_hell->in = 0;
	}
	if (s_hell->out != 1)
	{
		close(s_hell->out);
		s_hell->out = 1;
	}
}

void	close_fds(int oldfd[2])
{
	close(oldfd[0]);
	close(oldfd[1]);
}

void	exit_pipe(t_mini *s_hell)
{
	free_inputs(s_hell->envv);
	free(s_hell->pwd);
	exit(EXIT_SUCCESS);
}

int	my_brain(char *parsed_input, t_mini *s_hell, int piped)
{
	char	**inputs;
	int		cur_fd[2];

	if (my_error(parsed_input))
	{
		free(parsed_input);
		return (0);
	}
	setup_fds(cur_fd);
	parsed_input = format_input(parsed_input);
	my_redirections(&parsed_input, s_hell);
	parsed_input = format_input(parsed_input);
	inputs = split_input(parsed_input);
	if (!inputs)
		exit(EXIT_FAILURE);
	free(parsed_input);
	take_action(inputs, s_hell);
	free_inputs(inputs);
	dup2(cur_fd[0], 1);
	dup2(cur_fd[1], 0);
	close_reds(s_hell);
	close_fds(cur_fd);
	if (piped)
		exit_pipe(s_hell);
	return (0);
}
