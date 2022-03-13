#include "libft.h"

static char	**ft_strerror(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}

static int	ft_count(const char *s, char c)
{
	int	i;

	i = 0;
	while (*s && *s == c)
		s++;
	while (*s)
	{
		while (*s && *s != c)
			s++;
		i++;
		if (*s == '\0')
			return (i);
		while (*s == c && *s)
			s++;
	}
	return (i);
}

char	**ft_splitting(char **str, const char *s, char c, int len)
{
	int		i;
	size_t	k;
	size_t	j;

	i = 0;
	k = 0;
	while (i < len)
	{
		while (s[k] == c)
			k++;
		j = k;
		while (s[k] != c && s[k])
			k++;
		str[i] = ft_substr(s, j, (k - j));
		if (!str[i])
			return (ft_strerror(str));
		i++;
	}
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		len;

	if (!s)
		return (NULL);
	len = ft_count(s, c);
	str = malloc(sizeof(*str) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = NULL;
	return (ft_splitting(str, s, c, len));
}
