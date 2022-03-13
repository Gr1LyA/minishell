#include "libft.h"

static int	found_char(char s1, char const *set)
{
	while (*set)
	{
		if (*set == s1)
			return (0);
		set++;
	}
	return (1);
}

static unsigned int	found_start(char const *s1, char const *set)
{
	unsigned int	i;

	i = 0;
	while (s1[i])
	{
		if (found_char(s1[i], set))
			return (i);
		i++;
	}
	return (i);
}

static unsigned int	found_end(char const *s1, char const *set, size_t len)
{
	while (len > 0)
	{
		if (found_char(s1[len], set))
			return (len);
		len--;
	}
	return (len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t			len;
	unsigned int	start;

	if (!s1)
		return (NULL);
	if (ft_strlen(set) >= ft_strlen(s1))
		return (ft_substr(s1, 0, ft_strlen(s1)));
	len = ft_strlen(s1) - 1;
	start = found_start(s1, set);
	len = found_end(s1, set, len);
	if (start > len || !ft_strlen(s1))
		return (ft_substr(s1, 0, 0));
	return (ft_substr(s1, start, len - start + 1));
}
