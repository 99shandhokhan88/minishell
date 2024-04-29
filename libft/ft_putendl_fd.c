
#include "libft.h"

void	ft_putendl_fd(char *str, int fd)
{
	int count;

	if (str == NULL)
		return ;
	count = 0;
	while (str[count])
		count++;
	write(fd, str, count);
	write(fd, "\n", 1);
}
