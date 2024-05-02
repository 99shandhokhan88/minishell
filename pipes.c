/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzashev <vzashev@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 19:18:56 by vzashev           #+#    #+#             */
/*   Updated: 2024/05/02 02:46:39 by vzashev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_parents(char *input2, t_mini *s_hell, int *fd)
{
	int	oldfd;

	oldfd = dup(0);
	dup2(fd[0], 0);
	close(fd[0]);
	close(fd[1]);
	lexer(s_hell, input2);
	dup2(oldfd, 0);
	close(oldfd);
}

int	my_pipe(char *input1, char *input2, t_mini *s_hell)
{
	pid_t	pid;
	int		fds[2];

	if (pipe(fds) == -1)
	{
		perror("pipe");
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
	else if (pid < 0)
		exit(EXIT_FAILURE);
	else
		handle_parents(input2, s_hell, fds);
	waitpid(-1, NULL, 0);
	return (1);
}
