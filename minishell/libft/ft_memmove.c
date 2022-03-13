#include "libft.h"

void	*ft_memmove(void *destination, const void *source, size_t n)
{
	char		*s1;
	const char	*s2;

	if (destination == NULL && source == NULL)
		return (NULL);
	s1 = (char *)destination;
	s2 = (const char *)source;
	if (s1 < s2 || s2 + n < s1)
		return (ft_memcpy(s1, s2, n));
	while (n != 0)
	{
		n--;
		s1[n] = s2[n];
	}
	return (destination);
}
