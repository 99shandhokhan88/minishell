/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzashev <vzashev@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:19:39 by vzashev           #+#    #+#             */
/*   Updated: 2024/05/02 02:16:52 by vzashev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_env_pwd(t_mini *s_hell, char **cwd)
{
	char	*pwd;
	char	*oldpwd;

	pwd = join_str("PWD=", *cwd);
	if (!pwd)
		printf("Error: Failed to allocate memory for pwd\n");
	oldpwd = join_str("OLD", pwd);
	if (!oldpwd)
	{
		printf("Error: Failed to allocate memory for oldpwd\n");
		free(pwd);
	}
	replace_envv(oldpwd, s_hell, envv_index("OLDPWD=", s_hell));
	free(oldpwd);
	free(pwd);
}

void	change_pwd(t_mini *s_hell)
{
	char	*pwd;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		printf("Error retrieving current directory\n");
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
