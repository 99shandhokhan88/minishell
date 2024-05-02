/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzashev <vzashev@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 21:37:39 by vzashev           #+#    #+#             */
/*   Updated: 2024/05/02 18:18:46 by vzashev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_alpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int	is_alpha_or_digit(int x)
{
	return (is_alpha(x) || is_digit(x));
}

char	*sub_str(char const *str, unsigned int index, size_t len)
{
	char	*new;
	size_t	j;

	if (!str)
		return (NULL);
	if (index >= len_str(str))
		len = 0;
	new = alloc_with_zero(sizeof(char), (len + 1));
	if (!(new))
		return (NULL);
	j = 0;
	while (len-- && str[index])
	{
		new[j] = str[index];
		j++;
		index++;
	}
	new[j] = '\0';
	return (new);
}

size_t	len_my_itoa(int n)
{
	long int	num;
	int			len;

	num = n;
	len = 1;
	if (num < 0)
	{
		len++;
		num = -num;
	}
	while (num >= 10)
	{
		num = num / 10;
		len++;
	}
	return (len);
}

char	*my_itoa(int n)
{
	char		*str;
	long int	num;
	long int	len;

	len = len_my_itoa(n);
	num = n;
	str = alloc_with_zero(sizeof(char *), (len + 1));
	if (!str)
		return (NULL);
	if (num < 0)
	{
		num = -num;
		*str = '-';
	}
	str[len] = '\0';
	len--;
	while (num >= 10)
	{
		str[len] = 48 + (num % 10);
		num /= 10;
		len--;
	}
	if (num >= 0 && num < 10)
		str[len] = 48 + (num % 10);
	return (str);
}
