/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:42:42 by tharland          #+#    #+#             */
/*   Updated: 2022/03/21 15:42:43 by tharland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *destination, int c, size_t n)
{
	char	*str;
	size_t	i;

	str = (char *)destination;
	i = 0;
	while (i < n)
	{
		str[i] = c;
		i++;
	}
	return (destination);
}
