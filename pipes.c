/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzashev <vzashev@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:30:21 by vzashev           #+#    #+#             */
/*   Updated: 2024/05/03 19:29:53 by vzashev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
   This function handles parsing
   and executing commands separated by a pipe ('|').
   It splits the input into two parts
   at the position of the pipe,
   creates a new process to execute the first part,
   and sets up inter-process communication
   using a pipe. It then calls my_brain() to execute
   the second part in the child process
   and recursively invokes my_pipe() to handle additional pipes.
*/

int	pipe_pars(char *input, int pipe_pos, t_mini *s_hell)
{
	char	*new_input;
	int		space;

	space = 0;
	if (input[pipe_pos - 1] == ' ')
		space = 1;
	new_input = dup_str(&input[pipe_pos + 1]);
	input[pipe_pos - space] = '\0';
	return (my_pipe(input, new_input, s_hell));
}

/*
   This function checks if the current character
   in the input is a pipe ('|') or a dollar sign ('$').
   If it encounters a pipe,
   it calls pipe_pars() to handle pipe-related operations.
   If it encounters a dollar sign,
   it calls expander() to handle environment variable expansion.
*/

int	check_pipe_or_dollar(char **input, int *i, t_mini *s_hell)
{
	if ((*input)[*i] == '|')
	{
		pipe_pars((*input), *i, s_hell);
		return (1);
	}
	if ((*input)[*i] == '$')
		expander(s_hell, input, i);
	if ((*input)[*i] == '\'')
	{
		(*i)++;
		return (0);
	}
	(*i)++;
	return (0);
}

/*
   This function handles the parent process of a pipe.
   It duplicates the read end of the pipe to stdin,
   closes the pipe descriptors, and calls my_lexer()
   to execute the second part
   of the command in the child process.
*/

void	handle_parents(char *input2, t_mini *s_hell, int *fd)
{
	int	oldfd;

	oldfd = dup(0);
	dup2(fd[0], 0);
	close(fd[0]);
	close(fd[1]);
	my_lexer(s_hell, input2);
	dup2(oldfd, 0);
	close(oldfd);
}

/*
   This function implements the pipe functionality
   by creating a pipe using the pipe() system call,
   forking a child process to execute the first part
   of the command, and executing the second part
   in the parent process.
   It handles the inter-process communication
   and waits for the child process to finish.
*/

int	my_pipe(char *input1, char *input2, t_mini *s_hell)
{
	pid_t	pid;
	int		fds[2];

	if (pipe(fds) == -1)
	{
		perror("minishell: pipe error\n");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == 0)
	{
		free(input2);
		dup2(fds[1], 1);
		close(fds[0]);
		close(fds[1]);
		my_brain(input1, s_hell, 1);
	}
	else
	{
		free(input1);
		handle_parents(input2, s_hell, fds);
	}
	waitpid(-1, NULL, 0);
	return (1);
}
