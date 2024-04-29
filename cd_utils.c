
#include "minishell.h"

void	change_env_pwd(t_data *s_hell)
{
	char	*cwd;

	cwd = NULL;
	if (var_index("PWD", s_hell) >= 0)
		replace_var(ft_strjoin("PWD=", cwd), s_hell, var_index("PWD=", s_hell));
	else
		s_hell->env = export_env(s_hell->env, ft_strjoin("PWD=", cwd));
}

void	change_env_oldpwd(t_data *s_hell, char **cwd)
{
	char	*pwd;
	char	*oldpwd;

	pwd = ft_strjoin("PWD=", *cwd);
	if (!pwd)
	{
		printf("Error: Failed to allocate memory for pwd\n");
		return ;
	}
	oldpwd = ft_strjoin("OLD", pwd);
	if (!oldpwd)
	{
		printf("Error: Failed to allocate memory for oldpwd\n");
		free(pwd);
		return ;
	}
	replace_var(oldpwd, s_hell, var_index("OLDPWD=", s_hell));
	free(oldpwd);
	free(pwd);

}

void	change_pwd(t_data *s_hell)
{
	char	*pwd;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		printf("Error retrieving current directory\n");
		return ;
	}
	change_env_oldpwd(s_hell, &cwd);
	if (var_index("PWD", s_hell) >= 0)
	{
		pwd = ft_strjoin("PWD=", cwd);
		replace_var(pwd, s_hell, var_index(pwd, s_hell));
		free(pwd);
	}
	else
	{
		pwd = ft_strjoin("PWD=", cwd);
		s_hell->env = export_env(s_hell->env, pwd);
		free(pwd);
	}
	free(cwd);
}
