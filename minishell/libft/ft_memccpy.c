#include "libft.h"

void	*ft_memccpy(void	*dest, const void	*src, int c, size_t n)
{
	unsigned char			*s1;
	const unsigned char		*s2;
	size_t					i;

	s1 = dest;
	s2 = src;
	i = 0;
	while (i < n)
	{
		s1[i] = s2[i];
		if (s2[i] == (unsigned char) c)
			return (&s1[i + 1]);
		i++;
	}
	return (NULL);
}
