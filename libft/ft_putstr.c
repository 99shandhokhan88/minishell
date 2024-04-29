
#include "libft.h"

void	ft_putstr(char *str)
{
	int count;

	if (str == NULL)
	{
		write(1, "(null)", 6);
		return ;
	}
	count = 0;
	while (str[count])
		count++;
	write(1, str, count);
}
