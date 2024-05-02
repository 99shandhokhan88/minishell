/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzashev <vzashev@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:35:18 by vzashev           #+#    #+#             */
/*   Updated: 2024/05/02 02:42:04 by vzashev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	second_executor(char **inputs, t_mini *s_hell)
{
	int			i;
	char		**paths;
	int			index;
	struct stat	statounet;

	i = 0;
	statounet.st_mode = 0;
	index = envv_index("PATH=", s_hell);
	paths = gen_paths(index, s_hell, inputs[0]);
	while (paths[i])
	{
		stat(paths[i], &statounet);
		if ((statounet.st_mode & S_IXUSR)
			&& (execve(paths[i], inputs, s_hell->envv) != -1))
			return (0);
		i++;
	}
	free_envv(paths);
	return (1);
}

int	executor(char **inputs, t_mini *s_hell)
{
	int			index;
	struct stat	statounet;

	statounet.st_mode = 0;
	index = envv_index("PATH=", s_hell);
	stat(inputs[0], &statounet);
	if (str_char(inputs[0], '/') && (statounet.st_mode & S_IXUSR)
		&& (execve(inputs[0], &inputs[0], s_hell->envv) != -1))
		return (0);
	else if (index >= 0)
		if (!(second_executor(inputs, s_hell)))
			return (0);
	return (1);
}

void	my_exec(char **inputs, t_mini *s_hell)
{
	pid_t	pid;
	int		status;

	status = 0;
	if (!(check_exec_status(inputs, s_hell)))
		return (print_error("minishell: Unknown command\n", 127));
	pid = fork();
	if (pid == 0)
	{
		if (executor(inputs, s_hell) != 0)
			exit(errno);
		exit(EXIT_SUCCESS);
	}
	else if (pid < 0)
		exit(EXIT_FAILURE);
	else
		waitpid(pid, &status, 0);
	g_exit_status = WEXITSTATUS(status);
}
