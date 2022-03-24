/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:51:21 by tharland          #+#    #+#             */
/*   Updated: 2022/03/21 15:51:22 by tharland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_to_set(char **env, char *arg)
{
	size_t	i;
	int		m;
	char	*tmp;

	i = -1;
	if (arg[0] == '=' || (arg[0] >= '0' && arg[0] <= '9'))
		return (ERROR);
	m = ft_findchr(arg, '=');
	if (m != -1)
		return (SUCCESS);
	while (env[++i])
	{
		m = ft_findchr(env[i], '=');
		if (m != -1)
			tmp = ft_strndup(env[i], m);
		else
			tmp = ft_strndup(env[i], ft_strlen(env[i]));
		if (!ft_strncmp(arg, tmp, ft_strlen(tmp)))
		{
			free(tmp);
			return (ERROR);
		}
		free(tmp);
	}
	return (SUCCESS);
}

int	delimiter(char **env, char **vol, char *arg)
{
	int	m;

	m = ft_findchr(arg, '=');
	if (m == -1 || (size_t)m == ft_strlen(arg))
	{
		*vol = NULL;
		*env = ft_strdup(arg);
		if (!*env)
			return (error_mess("malloc"));
	}
	else
	{
		*env = ft_strndup(arg, m + 1);
		*vol = ft_strdup(arg + m + 1);
		if (!*env || !*vol)
			return (error_mess("malloc"));
	}
	return (SUCCESS);
}

int	set_env_export(t_mini *mini, char *env, char *vol)
{
	size_t	i;
	char	**envp;
	char	*tmp;

	tmp = ft_strndup(env, ft_strlen(env) - 1);
	if (!vol)
	{
		i = 0;
		while (mini->env[i])
			i++;
		envp = malloc(sizeof(char *) * (i + 2));
		if (!envp)
			return (error_mess("malloc"));
		envp[i + 1] = NULL;
		envp[0] = ft_strdup(env);
		i = -1;
		while (mini->env[++i])
			envp[i + 1] = mini->env[i];
		free(mini->env);
		mini->env = envp;
	}
	else
		set_env(mini, tmp, vol);
	free(tmp);
	return (SUCCESS);
}

int	ft_export(t_mini *mini)
{
	size_t	i;
	char	*env;
	char	*vol;

	i = 0;
	while (mini->pars->arg[i])
		i++;
	if (i == 1)
		return (print_sort_env(mini));
	i = 0;
	while (mini->pars->arg[++i])
	{
		if (check_to_set(mini->env, mini->pars->arg[i]))
			continue ;
		if (delimiter(&env, &vol, mini->pars->arg[i]))
			return (ERROR);
		if (set_env_export(mini, env, vol))
			return (ERROR);
		free(env);
		free(vol);
	}
	return (SUCCESS);
}
