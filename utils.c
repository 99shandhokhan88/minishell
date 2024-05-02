/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzashev <vzashev@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 19:23:13 by vzashev           #+#    #+#             */
/*   Updated: 2024/05/02 02:43:55 by vzashev          ###   ########.fr       */
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

void	s_hell_init(t_mini *s_hell)
{
	s_hell->in = 0;
	s_hell->out = 1;
	s_hell->red = 1;
}

size_t	custom_strspn(const char *str, const char *accept)
{
	const char	*space;
	const char	*letter;
	size_t		count;

	space = str;
	letter = accept;
	count = 0;
	while (*space)
	{
		while (*letter)
		{
			if (*space == *letter)
			{
				++count;
				break ;
			}
			++letter;
		}
		++space;
		if (!*letter)
			return (count);
	}
	return (count);
}

void	free_shell(t_mini *s_hell)
{
	int	i;

	i = 0;
	if (!s_hell->envv)
		return ;
	while (s_hell->envv[i])
	{
		free(s_hell->envv[i]);
		i++;
	}
	free(s_hell->envv);
}

int	check_pipe_at_beginning(char *input)
{
	if (input == NULL || input[0] == '\0')
		return (0);
	if (input[0] == '|')
	{
		printf("Error: wrong syntax!\n");
		return (1);
	}
	return (0);
}

int	is_digit(int n)
{
	return (n >= '0' && n <= '9');
}

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
	g_exit_status = status;
	print_str_fd(str, 2);
}

char	*str_str(const char *str, const char *to_find)
{
	size_t	i;
	int		j;

	i = 0;
	j = 0;
	if (to_find[j] == '\0')
		return ((char *)str);
	while (str[i])
	{
		while (str[i + j] == to_find[j] && str[i + j] != '\0')
			j++;
		if (to_find[j] == '\0')
			return ((char *)str + i);
		i++;
		j = 0;
	}
	return (0);
}

int	alpha_to_int(const char *str)
{
	long int	n;
	int			sign;

	n = 0;
	sign = 1;
	while ((*str <= 13 && *str >= 9) || *str == 32)
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			n = n * 10 + (*str++ - '0');
		else
			break ;
	}
	return ((int)(n * sign));
}

int	is_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (!is_digit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

size_t	count_word(const char *s, char c)
{
	size_t	words;

	words = 0;
	while (*s)
	{
		if (*s != c)
		{
			++words;
			while (*s && *s != c)
				++s;
		}
		else
			++s;
	}
	return (words);
}

char	**my_split(const char *s, char c)
{
	char	**str;
	size_t	i;
	size_t	len;

	if (!s)
		return (0);
	i = 0;
	str = alloc_with_zero(sizeof(char *), (count_word(s, c) + 1));
	if (!str)
		return (0);
	while (*s)
	{
		if (*s != c)
		{
			len = 0;
			while (*s && *s != c && ++len)
				++s;
			str[i++] = sub_str(s - len, 0, len);
		}
		else
			++s;
	}
	str[i] = 0;
	return (str);
}

void	my_dup2(int *fd, int arg)
{
	if (dup2(*fd, arg) == -1)
		exit(1);
	close(*fd);
}

int	my_atoi(const char *str)
{
	int	i;
	int	s;
	int	res;

	s = 1;
	i = 0;
	res = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == 32)
		i++;
	if (str[i] == '+')
	{
		i++;
	}
	else if (str[i] == '-')
	{
		s = -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		res = (str[i] - 48) + (res * 10);
		i++;
	}
	return (res * s);
}
