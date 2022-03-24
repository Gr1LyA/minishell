/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:44:00 by tharland          #+#    #+#             */
/*   Updated: 2022/03/21 15:44:04 by tharland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int ch)
{
	char	*s;

	s = (char *)str;
	if (ch == 0)
		return (s + ft_strlen(s));
	while (*s != '\0')
	{
		if (*s == (unsigned char) ch)
			return (s);
		s++;
	}
	return (NULL);
}
