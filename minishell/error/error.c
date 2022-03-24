/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:51:21 by tharland          #+#    #+#             */
/*   Updated: 2022/03/21 15:51:22 by tharland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	error_mess(char *str)
{
	char	*error_mess;

	error_mess = ft_strjoin("minishell: ", str);
	if (!error_mess)
		return (ERROR);
	perror(error_mess);
	free(error_mess);
	return (ERROR);
}
