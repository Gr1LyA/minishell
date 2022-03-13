#include "libft.h"

size_t	ft_strlcpy(char *str1, const char *str2, size_t n)
{
	size_t	i;

	i = 0;
	if (!n)
		return (ft_strlen(str2));
	if (!str1)
		return (n);
	while (i < n - 1 && str2[i] != '\0')
	{
		str1[i] = str2[i];
		i++;
	}
	str1[i] = '\0';
	return (ft_strlen(str2));
}
