/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzashev <vzashev@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:35:18 by vzashev           #+#    #+#             */
/*   Updated: 2024/05/01 18:43:52 by vzashev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_2(char **inputs, t_data *data)
{
	int			i;
	char		**paths;
	int			index;
	struct stat	statounet;

	i = 0;
	statounet.st_mode = 0;
	index = var_index("PATH=", data);
	paths = gen_paths(index, data, inputs[0]);
	while (paths[i])
	{
		stat(paths[i], &statounet);
		if ((statounet.st_mode & S_IXUSR)
			&& (execve(paths[i], inputs, data->env) != -1))
			return (0);
		i++;
	}
	free_env(paths);
	return (1);
}

int	execute(char **inputs, t_data *data)
{
	int			index;
	struct stat	statounet;

	statounet.st_mode = 0;
	index = var_index("PATH=", data);
	stat(inputs[0], &statounet);
	if (ft_strchr(inputs[0], '/') && (statounet.st_mode & S_IXUSR)
		&& (execve(inputs[0], &inputs[0], data->env) != -1))
		return (0);
	else if (index >= 0)
		if (!execute_2(inputs, data))
			return (0);
	return (1);
}

void	handle_exec(char **inputs, t_data *data)
{
	pid_t	pid;
	int		status;

	status = 0;
	if (!check_exec(inputs, data))
		return (error_sentence("minishell: Unknown command\n", 127));
	pid = fork();
	if (pid == 0)
	{
		if (execute(inputs, data) != 0)
			exit(errno);
		exit(EXIT_SUCCESS);
	}
	else if (pid < 0)
		exit(EXIT_FAILURE);
	else
		waitpid(pid, &status, 0);
	g_exit = WEXITSTATUS(status);
}
