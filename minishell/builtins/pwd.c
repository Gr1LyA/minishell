/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:51:28 by tharland          #+#    #+#             */
/*   Updated: 2022/03/21 15:51:29 by tharland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(void)
{
	char	*str;

	str = getcwd(0, 0);
	if (str)
	{
		ft_putstr_fd(str, STDOUT);
		ft_putstr_fd("\n", STDOUT);
		free(str);
		return (SUCCESS);
	}
	return (ERROR);
}
