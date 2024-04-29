
#include "libft.h"

static int	ft_setcheck(char const c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		else
			set++;
	}
	return (0);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	char	*new;
	size_t	newlen;

	if (!s1 || !set)
		return (NULL);
	while (ft_setcheck(*s1, set))
		s1++;
	if (!(*s1))
		return (new = ft_substr(s1, 0, 0));
	newlen = ft_strlen(s1);
	while (ft_setcheck(s1[newlen - 1], set))
		newlen--;
	if (!(new = malloc((newlen + 1) * sizeof(char))))
		return (NULL);
	ft_memmove(new, s1, newlen);
	new[newlen] = '\0';
	return (new);
}
