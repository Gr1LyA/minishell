#include "libft.h"

char	*ft_strchr(const char *str, int ch)
{
	char	*s;

	s = (char *)str;
	if (ch == 0)
		return (s + ft_strlen(s));
	while (*s != '\0')
	{
		if (*s == (unsigned char) ch)
			return (s);
		s++;
	}
	return (NULL);
}
