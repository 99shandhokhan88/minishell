
#include "minishell.h"

int	g_exit = 0;

void	end_of_file(t_data *data, char *user_input)
{
	free_env(data->env);
	free(user_input);
	free(data->pwd);
	ft_putstr_fd("exit\n", 2);
	exit(EXIT_SUCCESS);
}

void	data_init(t_data *data) //, char **env
{
	//data->env = dup_env(env);
	//data->pwd = getcwd(NULL, 0);
	data->fd_in = 0;
	data->fd_out = 1;
	data->redir = 1;
}

int		main(int ac, char **av, char **env)
{
	t_data	data;
	char	*input;

	(void)ac;
	(void)av;
	init_envv(env, &data);
	input = 0;
	data_init(&data);
	while (env)
	{
		setup_signals();
		input = readline("minishell$: ");
		if (input && input[0] && custom_strspn(input, " ") != len_str(input))
			add_history(input);
		if (input == NULL)
			handle_ctrl_d(&data, input);
		if (check_pipe_at_beginning(input))
			continue ;
		if (input && input[0] && custom_strspn(input, " ") != len_str(input))
			parser_start(input, &data);
		//free(input);
	}
	//free_shell(&data);
	return (0);
}
