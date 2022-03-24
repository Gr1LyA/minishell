/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:19:46 by tharland          #+#    #+#             */
/*   Updated: 2022/03/21 15:19:48 by tharland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_quote(t_mini *mini)
{
	while (mini->pars)
	{
		if (ft_quotes_arg(mini->pars))
			return (ERROR);
		if (ft_quotes_red(mini->pars->red))
			return (ERROR);
		mini->pars->red = mini->pars->head_red;
		mini->pars = mini->pars->next;
	}
	mini->pars = mini->head_pars;
	return (SUCCESS);
}
