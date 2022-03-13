#include "libft.h"

int	ft_isascii(int s)
{
	if (s >= 0 && s <= 127)
	{
		return (1);
	}
	return (0);
}
