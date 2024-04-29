
#include "libft.h"

static size_t	getputnbrlen(unsigned int n)
{
	size_t	i;

	i = 1;
	while (n /= 10)
		i++;
	return (i);
}

void			ft_putunbr(unsigned int n)
{
	size_t		len;
	int			div;
	char		c;

	div = 1;
	len = getputnbrlen(n);
	while (--len)
		div *= 10;
	while (div)
	{
		c = ((n / div) % 10) + '0';
		write(1, &c, 1);
		div /= 10;
	}
}
