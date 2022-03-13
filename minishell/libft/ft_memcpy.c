#include "libft.h"

void	*ft_memcpy(void *dest, const void *source, size_t count)
{
	unsigned char			*s1;
	const unsigned char		*s2;
	size_t					i;

	if (dest == NULL && source == NULL)
		return (NULL);
	s1 = (unsigned char *)dest;
	s2 = (const unsigned char *)source;
	i = 0;
	while (i < count)
	{
		s1[i] = s2[i];
		i++;
	}
	return (dest);
}
