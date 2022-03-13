#include "libft.h"

int	ft_isalpha(int s)
{
	if ((s >= 65 && s <= 90) || (s >= 97 && s <= 122))
		return (1);
	return (0);
}
