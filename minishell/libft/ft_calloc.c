/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:38:44 by tharland          #+#    #+#             */
/*   Updated: 2022/03/21 15:38:45 by tharland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
