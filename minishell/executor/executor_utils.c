/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:19:09 by tharland          #+#    #+#             */
/*   Updated: 2022/03/21 15:19:10 by tharland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	check_pipe(t_mini *mini)
{
	size_t	i;

	i = 0;
	if (!mini->pars)
		return (0);
	while (mini->pars->next)
	{
		i++;
		mini->pars = mini->pars->next;
	}
	mini->pars = mini->head_pars;
	return (i);
}

static char	*find_path2(char **path_split)
{
	size_t	i;
	char	*ret;

	i = 0;
	while (access(path_split[i], 1) != 0 && path_split[i])
		i++;
	if (!path_split[i])
	{
		i = 0;
		while (path_split[i])
			free(path_split[i++]);
		free(path_split);
		return (NULL);
	}
	ret = ft_strdup(path_split[i]);
	i = 0;
	while (path_split[i])
		free(path_split[i++]);
	free(path_split);
	return (ret);
}

char	*find_path(char *cmd, char *path)
{
	char	**path_split;
	size_t	i;
	char	*tmp;

	if (!path)
	{
		free(cmd);
		return (NULL);
	}
	path_split = ft_split(path, ':');
	i = 0;
	while (path_split[i])
	{
		tmp = path_split[i];
		path_split[i] = ft_strjoin(path_split[i], cmd);
		free(tmp);
		i++;
	}
	free(cmd);
	return (find_path2(path_split));
}
