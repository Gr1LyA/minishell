#include <stdlib.h>

void	*ft_memchr(const void *arr, int c, size_t n)
{
	const unsigned char	*str;
	size_t				i;

	str = arr;
	i = 0;
	while (i < n)
	{
		if (str[i] == (unsigned char) c)
			return ((unsigned char *)(str + i));
		i++;
	}
	return (NULL);
}
