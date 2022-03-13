#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*s;
	int		len;

	len = ft_strlen(str);
	s = malloc(sizeof(*s) * (len + 1));
	if (!s)
		return (NULL);
	while (len >= 0)
	{
		s[len] = str[len];
		len--;
	}
	return (s);
}
