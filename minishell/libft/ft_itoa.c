#include "libft.h"
#include <stdio.h>

void	ft_putnbr(long int n, char	*str, int	*i)
{
	if (n > 9)
		ft_putnbr(n / 10, str, i);
	str[*i] = n % 10 + '0';
	(*i)++;
}

int	ft_len_num(long int n)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		i++;
		n *= -1;
	}
	while (n > 9)
	{
		n /= 10;
		i++;
	}
	return (++i);
}

char	*ft_itoa(int n)
{
	char		*str;
	int			len;
	int			i;
	long int	num;

	i = 0;
	num = (long int)n;
	len = ft_len_num(num);
	str = malloc(sizeof(*str) * (len + 1));
	if (!str)
		return (NULL);
	if (num < 0)
	{
		str[i] = '-';
		i++;
		num *= -1;
	}
	ft_putnbr(num, str, &i);
	str[i] = '\0';
	return (str);
}
