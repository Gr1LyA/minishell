/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:18:37 by tharland          #+#    #+#             */
/*   Updated: 2022/03/21 15:18:39 by tharland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clean_env(t_mini *mini)
{
	size_t	i;

	i = 0;
	while (mini->env[i])
	{
		free(mini->env[i]);
		i++;
	}
	free(mini->env);
}

void	ft_del_lst(void *content)
{
	free(content);
}

void	clean_arg(t_mini *mini)
{
	size_t	i;

	if (mini->head_pars->arg)
	{
		i = 0;
		while (mini->head_pars->arg[i])
		{
			free(mini->head_pars->arg[i]);
			i++;
		}
		free(mini->head_pars->arg);
	}
}

void	ft_clean(t_mini *mini)
{
	void	*tmp;

	free(mini->path);
	while (mini->head_pars)
	{
		if (mini->head_pars->head_chunk)
			ft_lstclear(&(mini->head_pars->head_chunk), ft_del_lst);
		while (mini->head_pars->head_red)
		{
			free(mini->head_pars->head_red->name);
			tmp = mini->head_pars->head_red;
			mini->head_pars->head_red = mini->head_pars->head_red->next;
			free(tmp);
		}
		clean_arg(mini);
		tmp = mini->head_pars;
		mini->head_pars = mini->head_pars->next;
		free(tmp);
	}
	dup2(mini->out, STDOUT);
	dup2(mini->in, STDIN);
}
