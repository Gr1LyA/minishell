#include "libft.h"

void	*ft_calloc(int num, int size)
{
	void	*mass;

	mass = malloc(num * size);
	if (!mass)
		return (NULL);
	ft_bzero(mass, num * size);
	return (mass);
}
