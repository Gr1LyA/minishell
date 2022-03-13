#include "libft.h"

int	ft_isdigit(int s)
{
	if (s >= 48 && s <= 57)
	{
		return (1);
	}
	return (0);
}
