
#include "minishell.h"

void	free_env(char **env)
{
	int	i;
	int	env_len;

	i = 0;
	env_len = envlen(env);
	while (i < env_len)
		free(env[i++]);
	free(env);
}

int		envlen(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (++i);
}

char	**dup_env(char **env)
{
	char	**data_env;
	int		i;

	i = 0;
	data_env = alloc_with_zero(sizeof(char *), envlen(env));
	if (!data_env)
		exit(EXIT_FAILURE);
	while (env[i])
	{
		data_env[i] = ft_strdup(env[i]);
		i++;
	}
	data_env[i] = 0;
	return (data_env);
}

void	handle_env(char **env)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (env[i])
	{
		str = ft_strstr(env[i], "=");
		if (str)
		{
			j = 0;
			while (env[i][j])
			{
				write(1, &env[i][j], 1);
				j++;
			}
			write(1, "\n", 1);
		}
		i++;
	}
	g_exit = 0;
}

int	init_envv(char *env[], t_data *s_hell)
{
	int	i;

	i = 0;
	while (env && env[i])
		i++;
	s_hell->env = alloc_with_zero(sizeof(char *), (i + 1));
	if (!s_hell->env)
		return (0);
	i = 0;
	while (env && env[0] && env[i])
	{
		s_hell->env[i] = ft_strdup(env[i]);
		i++;
	}
	s_hell->env[i] = NULL;
	return (0);
}
