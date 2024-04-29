
#include "libft.h"

char	*ft_substr(char const *str, unsigned int index, size_t len)
{
	char	*new;
	size_t	j;

	if (!str)
		return (NULL);
	if (index >= ft_strlen(str))
		len = 0;
	if (!(new = malloc((len + 1) * sizeof(char))))
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
