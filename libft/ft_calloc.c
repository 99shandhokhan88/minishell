
#include "libft.h"

void	*ft_calloc(size_t n, size_t size)
{
	unsigned char	*ptr;

	ptr = malloc(n * size);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, n * size);
	return (ptr);
}
