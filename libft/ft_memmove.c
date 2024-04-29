
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char *ptr1;
	unsigned char *ptr2;

	if (dest == NULL && src == NULL)
		return (NULL);
	ptr1 = (unsigned char *)dest;
	ptr2 = (unsigned char *)src;
	if (ptr1 < ptr2)
		while (n--)
			*(ptr1++) = *(ptr2++);
	else
		while (n--)
			*(ptr1 + n) = *(ptr2 + n);
	return (dest);
}
