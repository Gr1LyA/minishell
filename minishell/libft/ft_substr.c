#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;

	if (!s)
		return (NULL);
	if (start >= (ft_strlen(s)))
	{
		str = malloc(sizeof(char *));
		if (!str)
			return (NULL);
		str[0] = '\0';
		return (str);
	}
	if ((ft_strlen(s)) < (start + len))
		len = ft_strlen(s) - start + 1;
	str = malloc(sizeof(*str) * (len + 1));
	if (!str)
		return (NULL);
	ft_memmove(str, &s[start], len);
	str[len] = '\0';
	return (str);
}
