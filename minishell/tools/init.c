/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:20:57 by tharland          #+#    #+#             */
/*   Updated: 2022/03/21 15:21:01 by tharland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_pars	*init_pars(void)
{
	t_pars	*pars;

	pars = malloc(sizeof(t_pars));
	if (!pars)
		return (NULL);
	pars->next = NULL;
	pars->arg = NULL;
	pars->red = NULL;
	pars->head_red = NULL;
	pars->chunk = NULL;
	pars->head_chunk = NULL;
	return (pars);
}

int	init_mini(t_mini *mini)
{
	mini->which_close = -1;
	mini->pars = NULL;
	mini->head_pars = NULL;
	if (get_path(mini))
		return (error_mess("malloc"));
	return (SUCCESS);
}
