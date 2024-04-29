
#include "libft.h"

char	*ft_strappend(char *str, char c)
{
	int		len;
	char	*new;
	int		i;

	len = ft_strlen(str);
	i = 0;
	new = malloc((len + 2) * sizeof(char));
	if (!new)
		exit(EXIT_FAILURE);
	while (str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[i++] = c;
	new[i] = '\0';
	return (new);
}

int		get_next_line(int fd, char **line)
{
	char	buf;
	char	*tmp;
	int		ret;

	buf = 0;
	*line = malloc(sizeof(char));
	if (!*line)
		exit(EXIT_FAILURE);
	**line = '\0';
	while (buf != '\n')
	{
		if ((ret = read(fd, &buf, 1)) && buf != '\n')
		{
			tmp = ft_strappend(*line, buf);
			free(*line);
			*line = tmp;
		}
		else if (!ret && !ft_strlen(*line))
			break ;
	}
	if (buf == '\n')
		return (1);
	else
		return (0);
}
