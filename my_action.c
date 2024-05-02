/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_action.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzashev <vzashev@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 09:42:44 by vzashev           #+#    #+#             */
/*   Updated: 2024/05/02 18:19:14 by vzashev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Function: take_action
 * ----------------------
 * Determines the action to be taken based on the command entered.
 *
 * inputs: An array of strings containing the command and its arguments.
 * s_hell: A pointer to the shell structure
 * containing environment variables and flags.
 */

void	take_action(char **inputs, t_mini *s_hell)
{
	if (!s_hell->red)
		s_hell->red = 1;
	if (!comp_str(inputs[0], "echo"))
		my_echo(inputs);
	else if (!comp_str(inputs[0], "cd"))
		my_cd(inputs, s_hell);
	else if (!comp_str(inputs[0], "pwd"))
		my_pwd();
	else if (!comp_str(inputs[0], "export"))
		my_export(inputs, s_hell);
	else if (!comp_str(inputs[0], "unset"))
		my_unset(inputs, s_hell);
	else if (!comp_str(inputs[0], "env"))
		my_envv(s_hell->envv);
	else if (!comp_str(inputs[0], "exit"))
		my_exit(inputs, s_hell);
	else
		my_exec(inputs, s_hell);
}
