/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:20:36 by tharland          #+#    #+#             */
/*   Updated: 2022/03/21 15:20:37 by tharland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strndup(const char *str, size_t len)
{
	char	*ret;

	ret = malloc(sizeof(char) * len + 1);
	if (!ret)
		return (NULL);
	ret[len] = '\0';
	ft_strlcpy(ret, str, len + 1);
	return (ret);
}
