/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzashev <vzashev@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 12:01:13 by vzashev           #+#    #+#             */
/*   Updated: 2024/05/02 18:19:04 by vzashev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Function: gen_paths
 * --------------------
 * Generates an array of absolute paths
 * by combining each path in the PATH environment variable
 * with the input command.
 *
 * index: The index of the PATH environment variable
 * in the shell environment variables array.
 * s_hell: A pointer to the shell structure.
 * input: The command to be executed.
 *
 * Returns: An array of absolute paths.
 */

char	**gen_paths(int index, t_mini *s_hell, char *input)
{
	char	*str;
	char	**paths;
	char	*temp;
	int		i;

	i = 0;
	str = dup_str(&s_hell->envv[index][5]);
	paths = my_split(str, ':');
	free(str);
	while (paths[i])
	{
		temp = paths[i];
		paths[i] = join_str(paths[i], "/");
		free(temp);
		temp = paths[i];
		paths[i] = join_str(paths[i], input);
		free(temp);
		i++;
	}
	return (paths);
}

/*
 * Function: check_exec_path
 * --------------------------
 * Checks if the command can be executed
 * from any of the paths listed in the PATH environment variable.
 *
 * inputs: An array containing the command
 * and its arguments.
 * s_hell: A pointer to the shell structure.
 *
 * Returns: 1 if the command is executable, 0 otherwise.
 */

int	check_exec_path(char **inputs, t_mini *s_hell)
{
	int			i;
	int			index;
	char		**paths;
	struct stat	statounet;

	statounet.st_mode = 0;
	i = 0;
	index = envv_index("PATH=", s_hell);
	if (envv_index("PATH=", s_hell) == -1)
		return (0);
	index = envv_index("PATH=", s_hell);
	paths = gen_paths(index, s_hell, inputs[0]);
	while (paths[i])
	{
		stat(paths[i], &statounet);
		if ((statounet.st_mode & S_IXUSR) && !(statounet.st_mode & __S_IFDIR))
		{
			free_envv(paths);
			return (1);
		}
		i++;
	}
	free_envv(paths);
	return (0);
}

/*
 * Function: check_exec_status
 * ----------------------------
 * Checks the execution status of the command
 * by verifying if it is executable
 * from the current directory or the PATH environment variable.
 *
 * inputs: An array containing the command and its arguments.
 * s_hell: A pointer to the shell structure.
 *
 * Returns: 1 if the command is executable, 0 otherwise.
 */

int	check_exec_status(char **inputs, t_mini *s_hell)
{
	int			ret;
	struct stat	statounet;

	statounet.st_mode = 0;
	ret = 0;
	stat(inputs[0], &statounet);
	if (str_char(inputs[0], '/') && (statounet.st_mode & S_IXUSR)
		&& !(statounet.st_mode & __S_IFDIR))
		ret = 1;
	else
		ret = check_exec_path(inputs, s_hell);
	return (ret);
}
