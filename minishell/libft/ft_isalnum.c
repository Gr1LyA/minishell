#include "libft.h"

int	ft_isalnum(int s)
{
	if ((s >= 48 && s <= 57) || (s >= 65 && s <= 90) || (s >= 97 && s <= 122))
	{
		return (1);
	}
	return (0);
}
