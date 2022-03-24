/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dest.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:19:21 by tharland          #+#    #+#             */
/*   Updated: 2022/03/21 15:19:22 by tharland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	sub_ft_dest_arg(t_pars *pars, size_t i)
{
	pars->arg = malloc(sizeof(char **) * (i + 1));
	if (!pars->arg)
		return (ERROR);
	pars->arg[i] = NULL;
	i = 0;
	while (pars->chunk)
	{
		if (*(char *)pars->chunk->content != '<'
			&& *(char *)pars->chunk->content != '>')
		{
			pars->arg[i] = ft_strdup((char *)pars->chunk->content);
			if (!pars->arg[i])
				return (ERROR);
			i++;
		}
		pars->chunk = pars->chunk->next;
	}
	pars->chunk = pars->head_chunk;
	return (SUCCESS);
}

int	ft_dest_arg(t_mini *mini)
{
	size_t	i;

	while (mini->pars)
	{
		i = 0;
		while (mini->pars->chunk)
		{
			if (*(char *)mini->pars->chunk->content != '<'
				&& *(char *)mini->pars->chunk->content != '>')
				i++;
			mini->pars->chunk = mini->pars->chunk->next;
		}
		mini->pars->chunk = mini->pars->head_chunk;
		if (sub_ft_dest_arg(mini->pars, i))
			return (ERROR);
		mini->pars = mini->pars->next;
	}
	mini->pars = mini->head_pars;
	return (SUCCESS);
}
