/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzashev <vzashev@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:52:34 by vzashev           #+#    #+#             */
/*   Updated: 2024/05/02 00:36:34 by vzashev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;

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
			lexer(&s_hell, input);
	}
	return (0);
}
