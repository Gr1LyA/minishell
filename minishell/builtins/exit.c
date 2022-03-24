/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:51:12 by tharland          #+#    #+#             */
/*   Updated: 2022/03/21 15:51:14 by tharland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_check_exit(const char *str)
{
	size_t	i;
	size_t	len;

	len = ft_strlen(str);
	i = -1;
	while (++i < len)
	{
		if (i == 0)
		{
			if (!(str[i] == '-' || str[i] == '+' || ft_isdigit(str[i])))
				return (255);
		}
		else
		{
			if (!ft_isdigit(str[i]))
				return (255);
		}
	}
	return (0);
}

static int	ft_exit_atoi(const char *str)
{
	short			sign;
	unsigned char	result;

	result = 0;
	sign = 1;
	if (*str == '-')
	{
		sign = -1;
		++str;
	}
	else if (*str == '+')
		++str;
	while ('0' <= *str && *str <= '9')
	{
		result = 10 * result + (*str - '0');
		++str;
	}
	return (result * sign);
}

int	ft_exit(t_mini *mini)
{
	size_t	len;

	write(2, "exit\n", 5);
	len = 1;
	while (mini->pars->arg[len])
		len ++;
	if (len == 1)
		exit (0);
	else if (ft_check_exit(mini->pars->arg[1]))
	{
		write(2, "minishell: exit: ", 17);
		ft_putstr_fd(mini->pars->arg[1], 2);
		write(2, ": numeric argument required\n", 28);
		exit(2);
	}
	else if (len > 2)
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		return (ERROR);
	}
	exit(ft_exit_atoi(mini->pars->arg[1]));
	return (1);
}
