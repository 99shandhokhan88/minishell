
#include "minishell.h"

void	handle_parentps(char *input2, t_data *data, int *fd)
{
	int		oldfd;
	//int		status;

/*
	if (waitpid(pid, &status, 0) != pid)
		exit(EXIT_FAILURE);
	free(g_user_input);
	g_user_input = NULL;
	oldfd = dup(0);
	dup2(fds[0], 0);
	close(fds[0]);
	close(fds[1]);
	parser_start(input2, data);
	dup2(oldfd, 0);
	close(oldfd);
*/
	oldfd = dup(0);
	dup2(fd[0], 0);
	close(fd[0]);
	close(fd[1]);
	parser_start(input2, data);
	dup2(oldfd, 0);
	close(oldfd);
	//free(input2);
}

int		handle_pipe(char *input1, char *input2, t_data *data)
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
	{
		//free(input1);
		//input1 = NULL;
		//handle_parentps(input2, data, pid, fds);
		handle_parentps(input2, data, fds);
	}
	waitpid(-1, NULL, 0);
	//free(input1);
	//free(input2);
	return (1);
}
