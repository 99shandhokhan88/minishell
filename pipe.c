/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzashev <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 19:18:56 by vzashev           #+#    #+#             */
/*   Updated: 2024/05/01 19:20:05 by vzashev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_parentps(char *input2, t_data *data, int *fd)
{
	int	oldfd;

	oldfd = dup(0);
	dup2(fd[0], 0);
	close(fd[0]);
	close(fd[1]);
	parser_start(input2, data);
	dup2(oldfd, 0);
	close(oldfd);
}

int	handle_pipe(char *input1, char *input2, t_data *data)
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
		handle_basic(input1, data, 1);
	}
	else if (pid < 0)
		exit(EXIT_FAILURE);
	else
		handle_parentps(input2, data, fds);
	waitpid(-1, NULL, 0);
	return (1);
}
