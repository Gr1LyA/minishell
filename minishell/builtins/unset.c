/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:51:35 by tharland          #+#    #+#             */
/*   Updated: 2022/03/21 15:51:37 by tharland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	unset(t_mini *mini, size_t i)
{
	size_t	j;
	size_t	k;
	size_t	len;
	char	**new_env;

	j = 0;
	while (mini->env[j])
		j++;
	len = j - 1;
	new_env = malloc(sizeof(char *) * (len + 1));
	if (!new_env)
		return (error_mess("malloc"));
	new_env[len] = NULL;
	j = 0;
	k = 0;
	while (j < len)
	{
		if (k == i)
			k++;
		new_env[j++] = mini->env[k++];
	}
	free(mini->env[i]);
	free(mini->env);
	mini->env = new_env;
	return (SUCCESS);
}

int	unset_one(t_mini *mini, char *arg)
{
	size_t	i;

	i = -1;
	while (mini->env[++i])
	{
		if (!ft_strncmp(arg, mini->env[i], ft_findchr(mini->env[i], '=')))
			return (unset(mini, i));
	}
	return (SUCCESS);
}

int	ft_unset(t_mini *mini)
{
	size_t	i;
	int		ret;

	if (!mini->pars->arg[1])
		return (SUCCESS);
	ret = 0;
	i = 0;
	while (mini->pars->arg[++i])
		ret = unset_one(mini, mini->pars->arg[i]);
	return (ret);
}
