/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:50:58 by tharland          #+#    #+#             */
/*   Updated: 2022/03/21 15:51:00 by tharland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo(char **str)
{
	int	flag;
	int	i;

	i = 1;
	flag = 1;
	if (str[i])
		flag = ft_strncmp("-n", str[i], 3);
	if (!flag)
		i++;
	while (str[i])
	{
		ft_putstr_fd(str[i], STDOUT);
		i++;
		if (str[i])
			ft_putstr_fd(" ", STDOUT);
	}
	if (flag != 0)
		ft_putstr_fd("\n", STDOUT);
	return (SUCCESS);
}
