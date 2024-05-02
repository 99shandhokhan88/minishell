/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzashev <vzashev@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:34:23 by vzashev           #+#    #+#             */
/*   Updated: 2024/05/02 02:42:01 by vzashev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
