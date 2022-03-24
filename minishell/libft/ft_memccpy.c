/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:41:43 by tharland          #+#    #+#             */
/*   Updated: 2022/03/21 15:41:44 by tharland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void	*dest, const void	*src, int c, size_t n)
{
	unsigned char			*s1;
	const unsigned char		*s2;
	size_t					i;

	s1 = dest;
	s2 = src;
	i = 0;
	while (i < n)
	{
		s1[i] = s2[i];
		if (s2[i] == (unsigned char) c)
			return (&s1[i + 1]);
		i++;
	}
	return (NULL);
}
