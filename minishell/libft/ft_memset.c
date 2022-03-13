#include "libft.h"

void	*ft_memset(void *destination, int c, size_t n)
{
	char	*str;
	size_t	i;

	str = (char *)destination;
	i = 0;
	while (i < n)
	{
		str[i] = c;
		i++;
	}
	return (destination);
}
