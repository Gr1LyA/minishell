#include "libft.h"
// #include "stdio.h"

size_t	ft_strlcat(char *str1, const char *str2, size_t n)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	while (str1[i] && i < n)
		i++;
	while (i + 1 < n && str2[j])
	{
		str1[i] = str2[j];
		i++;
		j++;
	}
	if (i < n)
		str1[i] = '\0';
	return (i - j + ft_strlen(str2));
}
