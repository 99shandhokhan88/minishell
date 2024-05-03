/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_brain.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzashev <vzashev@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 13:38:56 by vzashev           #+#    #+#             */
/*   Updated: 2024/05/03 19:39:49 by vzashev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Function: setup_fds
 * --------------------
 * Duplicates standard input and output file descriptors.
 *
 * newfd: An array to store the duplicated file descriptors.
 */

void	setup_fds(int newfd[2])
{
	newfd[0] = dup(1);
	newfd[1] = dup(0);
}

/*
 * Function: close_reds
 * ---------------------
 * Closes input and output file descriptors if they are not standard.
 *
 * s_hell: A pointer to the shell structure containing file descriptors.
 */

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

/*
 * Function: close_fds
 * --------------------
 * Closes file descriptors used for inter-process communication.
 *
 * oldfd: An array containing file descriptors to be closed.
 */

void	close_fds(int oldfd[2])
{
	close(oldfd[0]);
	close(oldfd[1]);
}

/*
 * Function: exit_pipe
 * --------------------
 * Frees memory and exits the shell process.
 *
 * s_hell: A pointer to the shell structure.
 */

void	exit_pipe(t_mini *s_hell)
{
	free_inputs(s_hell->envv);
	exit(EXIT_SUCCESS);
}

/*
 * Function: my_brain
 * -------------------
 * Executes the parsed input command and manages redirections and pipes.
 *
 * parsed_input: The parsed input command string.
 * s_hell: A pointer to the shell structure
 * containing environment variables and flags.
 * piped: A flag indicating whether the command is piped.
 *
 * Returns: 0 on successful execution.
 */

int	my_brain(char *parsed_input, t_mini *s_hell, int pipe)
{
	char	**inputs;
	int		cur_fd[2];
	char	*test1;
	char	*test2;

	if (my_error(parsed_input))
	{
		free(parsed_input);
		return (0);
	}
	setup_fds(cur_fd);
	test1 = format_input(parsed_input);
	free(parsed_input);
	my_redirections(&test1, s_hell);
	test2 = format_input(test1);
	free(test1);
	inputs = split_input(test2);
	free(test2);
	take_action(inputs, s_hell);
	free_inputs(inputs);
	osema(cur_fd, s_hell);
	close_fds(cur_fd);
	if (pipe)
		exit_pipe(s_hell);
	return (0);
}
