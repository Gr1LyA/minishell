/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:20:50 by tharland          #+#    #+#             */
/*   Updated: 2022/03/21 15:20:51 by tharland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_path(t_mini *mini)
{
	size_t	i;

	i = 0;
	while (mini->env[i])
	{
		if (!ft_strncmp("PATH=", mini->env[i], 5))
		{
			mini->path = ft_strdup(mini->env[i] + 5);
			if (!mini->path)
				return (ERROR);
			return (SUCCESS);
		}
		i++;
	}
	mini->path = NULL;
	return (SUCCESS);
}
