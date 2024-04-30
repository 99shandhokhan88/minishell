
#include "minishell.h"

void	handle_sig(int sig)
{
	if (sig == SIGINT)
	{
		g_exit = 130;
		//if (g_user_input)
		//	ft_putstr_fd("\nminishell> ", 2);
		//if (g_user_input)
		//	free(g_user_input);
		//g_user_input = ft_strdup("\0");
	}
	else if (sig == SIGQUIT)
		write(2, "\b\b  \b\b", 6);
}

void	sig_init(void)
{
	if (signal(SIGINT, handle_sig) == SIG_ERR)
		exit(EXIT_FAILURE);
	else if (signal(SIGQUIT, handle_sig) == SIG_ERR)
		exit(EXIT_FAILURE);
}

void	handle_exec_sig(int sig)
{
	if (sig == SIGINT)
	{
		//if (g_user_input)
		//	free(g_user_input);
		g_exit = 130;
		//g_quit = 1;
		write(2, "\n", 1);
	}
	else if (sig == SIGQUIT)
	{
		g_exit = 131;
		ft_putstr_fd("Exit (core dumped)\n", 2);
	}
}

void	sig_exec_init(void)
{
	if (signal(SIGINT, handle_exec_sig) == SIG_ERR)
		exit(EXIT_FAILURE);
	else if (signal(SIGQUIT, handle_exec_sig) == SIG_ERR)
		exit(EXIT_FAILURE);
}

 void	handle_ctrl_c(int sig)
{
	if (sig == SIGINT)
	{
		g_exit = 130;
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	setup_signals(void)
{
	signal(SIGINT, handle_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

void	handle_ctrl_d(t_data *s_hell, char *input)
{
	free_shell(s_hell);
	if (input)
		free(input);
	exit(g_exit);
}
