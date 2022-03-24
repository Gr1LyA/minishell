/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:42:20 by tharland          #+#    #+#             */
/*   Updated: 2022/03/21 15:42:21 by tharland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *source, size_t count)
{
	unsigned char			*s1;
	const unsigned char		*s2;
	size_t					i;

	if (dest == NULL && source == NULL)
		return (NULL);
	s1 = (unsigned char *)dest;
	s2 = (const unsigned char *)source;
	i = 0;
	while (i < count)
	{
		s1[i] = s2[i];
		i++;
	}
	return (dest);
}
