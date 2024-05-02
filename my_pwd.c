/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzashev <vzashev@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 23:32:03 by vzashev           #+#    #+#             */
/*   Updated: 2024/05/02 22:19:11 by vzashev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
   This function prints the current working directory (PWD).
   It uses the getcwd() function to retrieve the current working directory.
   The path is then printed to the standard output.
   Finally, it frees the memory allocated for the path.
*/

void	my_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	printf("%s\n", path);
	free(path);
	g_exit = 0;
}
