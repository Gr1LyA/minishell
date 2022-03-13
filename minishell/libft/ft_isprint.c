#include "libft.h"

int	ft_isprint(int s)
{
	if (s >= 32 && s <= 126)
	{
		return (1);
	}
	return (0);
}
