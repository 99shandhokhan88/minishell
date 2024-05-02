/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzashev <vzashev@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 02:34:49 by vzashev           #+#    #+#             */
/*   Updated: 2024/05/02 02:43:19 by vzashev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
