#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t size)
{
	size_t	j;
	size_t	i;
	size_t	k;

	if (!*needle)
		return ((char *)haystack);
	if (size > ft_strlen(haystack))
		size = ft_strlen(haystack);
	i = 0;
	while (i < size)
	{
		j = 0;
		k = i;
		while (haystack[k] == needle[j] && k < size)
		{
			k++;
			j++;
			if (needle[j] == '\0')
				return ((char *)(haystack + k - j));
		}
		i++;
	}
	return (NULL);
}
