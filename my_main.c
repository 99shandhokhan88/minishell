/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzashev <vzashev@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 10:18:42 by vzashev           #+#    #+#             */
/*   Updated: 2024/05/02 22:57:36 by vzashev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Global variable to store the exit status of
 * the most recently executed command.
 *
 * Initialized to 0, indicating successful execution
 * by default.
 */

int	g_exit = 0;

/*
 * Function: main
 * --------------
 * Entry point of the minishell program. Initializes environment variables,
 * sets up signal handlers, reads user input, and invokes the lexer.
 *
 * argc: Number of command-line arguments.
 * argv: Array of command-line arguments.
 * envv: Array of environment variables.
 *
 * Returns: 0 on successful execution.
 */

int	main(int argc, char *argv[], char *envv[])
{
	char	*input;
	t_mini	s_hell;

	(void)argc;
	(void)argv;
	init_envv(envv, &s_hell);
	input = 0;
	s_hell_init(&s_hell);
	while (envv)
	{
		setup_signals();
		input = readline("minishell$: ");
		if (input && input[0] && custom_strspn(input, " ") != len_str(input))
			add_history(input);
		if (input == NULL)
			handle_ctrl_d(&s_hell, input);
		if (check_pipe_at_beginning(input))
			continue ;
		if (input && input[0] && custom_strspn(input, " ") != len_str(input))
			my_lexer(&s_hell, input);
	}
	return (0);
}
