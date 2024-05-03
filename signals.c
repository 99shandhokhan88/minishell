/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzashev <vzashev@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 13:02:24 by vzashev           #+#    #+#             */
/*   Updated: 2024/05/03 19:51:21 by vzashev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
   This function handles the SIGINT signal (Ctrl+C)
   by setting up a signal handler.
   When the SIGINT signal is received,
   it sets the global exit status to 130 (indicating termination by Ctrl+C),
   prints a newline character to start a new line,
   clears the current input line using rl_replace_line(),
   moves the cursor to the beginning
   of the line using rl_on_new_line(),
   and redisplays the line using rl_redisplay().
*/

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

/*
   This function sets up the signal handlers
   for SIGINT (Ctrl+C), SIGQUIT, and SIGTSTP.
   It ignores SIGQUIT and SIGTSTP signals.
*/

void	setup_signals(void)
{
	signal(SIGINT, handle_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

/*
   This function handles the termination
   of the shell when Ctrl+D is pressed.
   It frees the allocated memory
   for the shell structure, input buffer,
   and exits with the global exit status.
*/

void	handle_ctrl_d(t_mini *s_hell, char *input)
{
	free_shell(s_hell);
	if (input)
		free(input);
	exit(g_exit);
}

void	osema(int cur_fd[2], t_mini *s_hell)
{
	dup2(cur_fd[0], 1);
	dup2(cur_fd[1], 0);
	close_reds(s_hell);
}
