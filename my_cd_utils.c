/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzashev <vzashev@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 22:21:10 by vzashev           #+#    #+#             */
/*   Updated: 2024/05/02 22:20:52 by vzashev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Function: cd_one
 * -----------------
 * Changes the current directory to the user's home directory.
 *
 * s_hell: A pointer to the shell structure.
 *
 * Returns: 1 on success, 0 on failure.
 */

int	cd_one(t_mini *s_hell)
{
	if (envv_index("HOME=", s_hell) < 0
		|| chdir((str_char(s_hell->envv[envv_index("HOME=", s_hell)], '=') + 1))
		== -1)
		return (0);
	change_my_pwd(s_hell);
	return (1);
}

/*
 * Function: cd_two
 * -----------------
 * Changes the current directory to the previous working directory.
 *
 * s_hell: A pointer to the shell structure.
 *
 * Returns: 1 on success, 0 on failure.
 */

int	cd_two(t_mini *s_hell)
{
	if (envv_index("OLDPWD=", s_hell) < 0
		|| chdir((str_char(s_hell->envv[envv_index("OLDPWD=", s_hell)], '=')
				+ 1)) == -1)
		return (0);
	change_my_pwd(s_hell);
	return (1);
}

/*
 * Function: cd_pwd
 * -----------------
 * Changes the current directory to the specified path.
 *
 * args: An array containing the command and path arguments.
 * s_hell: A pointer to the shell structure.
 *
 * Returns: 1 on success, 0 on failure.
 */

int	cd_pwd(char **args, t_mini *s_hell)
{
	if (chdir(args[1]) == -1)
		return (0);
	change_my_pwd(s_hell);
	return (1);
}

/*
 * Function: change_env_pwd
 * -------------------------
 * Updates the environment variables
 * for the current and previous working directories.
 *
 * s_hell: A pointer to the shell structure.
 * cwd: A pointer to the current working directory path.
 */

void	change_env_pwd(t_mini *s_hell, char **cwd)
{
	char	*pwd;
	char	*old_pwd;

	pwd = join_str("PWD=", *cwd);
	if (!pwd)
		printf("Error: failed allocation PWD!\n");
	old_pwd = join_str("OLD", pwd);
	if (!old_pwd)
	{
		printf("Error: failed allocation OLDPWD!\n");
		free(pwd);
	}
	replace_envv(old_pwd, s_hell, envv_index("OLDPWD=", s_hell));
	free(old_pwd);
	free(pwd);
}

/*
 * Function: change_my_pwd
 * ---------------------
 * Updates the environment variables and changes the current working directory.
 *
 * s_hell: A pointer to the shell structure.
 */

void	change_my_pwd(t_mini *s_hell)
{
	char	*pwd;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		printf("Error: undefined current directory!\n");
	change_env_pwd(s_hell, &cwd);
	if (envv_index("PWD", s_hell) >= 0)
	{
		pwd = join_str("PWD=", cwd);
		replace_envv(pwd, s_hell, envv_index(pwd, s_hell));
		free(pwd);
	}
	else
	{
		pwd = join_str("PWD=", cwd);
		s_hell->envv = export_envv(s_hell->envv, pwd);
		free(pwd);
	}
	free(cwd);
}
