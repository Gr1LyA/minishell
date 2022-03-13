#include "libft.h"

int	ft_atoi(const char *str)
{
	int	res;
	int	znak;

	znak = 1;
	res = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
	{
		znak *= -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9' && *str != '\0')
	{
		res = res * 10 + *str - 48;
		str++;
	}
	return (res * znak);
}
