/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzashev <vzashev@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 01:39:42 by vzashev           #+#    #+#             */
/*   Updated: 2024/05/02 22:19:17 by vzashev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_str(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	j = 0;
	i = 0;
	str = alloc_with_zero(sizeof(char), (len_str(s1) + len_str(s2) + 1));
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

int	comp_str(const char *s1, const char *s2)
{
	unsigned int	i;
	unsigned char	*p1;
	unsigned char	*p2;

	p1 = (unsigned char *)s1;
	p2 = (unsigned char *)s2;
	i = 0;
	while (p1[i] || p2[i])
	{
		if (p1[i] != p2[i])
			return (p1[i] - p2[i]);
		i++;
	}
	return (0);
}

char	*str_char(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (i < len_str(s) + 1)
	{
		if (*(s + i) == (char)c)
			return ((char *)(s + i));
		i++;
	}
	return (NULL);
}

void	print_str_fd(char *str, int fd)
{
	int	count;

	count = 0;
	if (str == NULL)
		return ;
	while (str[count])
		count++;
	write(fd, str, count);
}

void	print_error(char *str, int status)
{
	g_exit = status;
	print_str_fd(str, 2);
}
