
#include "libft.h"

static size_t	getputnbrlen(long int n)
{
	size_t	i;

	i = 1;
	while (n /= 10)
		i++;
	return (i);
}

void			ft_putnbr(int n)
{
	long int	num;
	size_t		len;
	int			div;
	char		c;

	num = n;
	div = 1;
	if (n < 0)
	{
		num = -num;
		write(1, "-", 1);
	}
	len = getputnbrlen(num);
	while (--len)
		div *= 10;
	while (div)
	{
		c = ((num / div) % 10) + '0';
		write(1, &c, 1);
		div /= 10;
	}
}
