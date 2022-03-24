/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:20:43 by tharland          #+#    #+#             */
/*   Updated: 2022/03/21 15:20:45 by tharland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	sub_set_env(t_mini *mini, char *env, char *vol)
{
	char	*tmp;
	char	*ret;
	size_t	i;
	char	**new_env;

	tmp = ft_strjoin(env, "=");
	ret = ft_strjoin(tmp, vol);
	free(tmp);
	if (!tmp || !ret)
		return (error_mess("malloc"));
	i = 0;
	while (mini->env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return (error_mess("malloc"));
	new_env[i + 1] = NULL;
	i = -1;
	new_env[0] = ret;
	while (mini->env[++i])
		new_env[i + 1] = mini->env[i];
	free(mini->env);
	mini->env = new_env;
	return (SUCCESS);
}

int	set_env(t_mini *mini, char *env, char *vol)
{
	size_t	i;
	char	*ret;
	char	*tmp;

	i = 0;
	while (mini->env[i])
	{
		if (!ft_strncmp(env, mini->env[i], ft_strlen(env))
			&& (mini->env[i][ft_strlen(env)] == '='
			|| mini->env[i][ft_strlen(env)] == '\0'))
		{
			tmp = ft_strndup(mini->env[i], ft_strlen(env));
			ret = ft_strjoin(tmp, "=");
			free(tmp);
			tmp = ft_strjoin(ret, vol);
			if (!tmp)
				return (error_mess("malloc"));
			free(ret);
			free(mini->env[i]);
			mini->env[i] = tmp;
			return (SUCCESS);
		}
		i++;
	}
	return (sub_set_env(mini, env, vol));
}

char	*get_env(t_mini *mini, char *str)
{
	size_t	i;
	char	*ret;

	i = 0;
	while (mini->env[i])
	{
		if (!ft_strncmp(str, mini->env[i], ft_strlen(str)))
		{
			ret = ft_strdup(mini->env[i] + ft_findchr(mini->env[i], '=') + 1);
			if (!ret)
				error_mess("malloc");
			return (ret);
		}
		i++;
	}
	return (NULL);
}

int	init_env(t_mini *mini, char **envp)
{
	size_t	i;
	char	*sh;

	i = 0;
	while (envp[i])
		i++;
	mini->env = malloc(sizeof(char *) * (i + 1));
	if (!(mini->env))
		return (ERROR);
	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], "SHLVL", ft_findchr(envp[i], '=')))
		{
			sh = ft_itoa(ft_atoi(envp[i] + ft_findchr(envp[i], '=') + 1) + 1);
			mini->env[i] = ft_strjoin("SHLVL=", sh);
			free(sh);
		}
		else
			mini->env[i] = ft_strdup(envp[i]);
		if (!(mini->env[i]))
			return (ERROR);
	}
	mini->env[i] = NULL;
	return (SUCCESS);
}
