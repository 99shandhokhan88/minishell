/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzashev <vzashev@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 00:02:32 by vzashev           #+#    #+#             */
/*   Updated: 2024/05/02 18:18:48 by vzashev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*set_to_zero(void *space, int zero, size_t dimension)
{
	unsigned char	*temp;
	size_t			i;

	temp = (unsigned char *)space;
	i = 0;
	while (i < dimension)
		temp[i++] = zero;
	return (space);
}

void	*alloc_with_zero(size_t type_count, size_t size)
{
	void	*res;
	int		len;

	if (type_count == SIZE_MAX || size == SIZE_MAX)
		return (NULL);
	len = type_count * size;
	res = (void *) malloc(len);
	if (res == NULL)
		return (NULL);
	set_to_zero(res, '\0', len);
	return (res);
}

size_t	len_str(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*copy_str(char *copy, const char *original)
{
	int	i;

	i = 0;
	while (original[i])
	{
		copy[i] = original[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

char	*dup_str(const char *src)
{
	char	*dest;

	dest = alloc_with_zero(sizeof(char), (len_str(src) + 1));
	if (dest == NULL)
		return (NULL);
	copy_str(dest, src);
	return (dest);
}
