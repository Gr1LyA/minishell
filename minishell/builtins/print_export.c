/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:51:21 by tharland          #+#    #+#             */
/*   Updated: 2022/03/21 15:51:22 by tharland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_strcmp(char *a, char *b)
{
	while (*a != '\0' && *a == *b)
	{
		a++;
		b++;
	}
	return (*b - *a);
}

static int	init_mass(char ***dest, char **srcs)
{
	size_t	i;

	i = 0;
	while (srcs[i])
		i++;
	(*dest) = malloc(sizeof(char *) * (i + 1));
	if (!(*dest))
		return (ERROR);
	(*dest)[i] = NULL;
	i = -1;
	while (srcs[++i])
		(*dest)[i] = srcs[i];
	return (SUCCESS);
}

static int	print_export(char **sort_env)
{
	size_t	i;
	int		m;
	char	*tmp;

	i = -1;
	while (sort_env[++i])
	{
		m = ft_findchr(sort_env[i], '=');
		if (m == -1)
			printf("declare -x %s\n", sort_env[i]);
		else
		{
			tmp = sort_env[i];
			printf("declare -x %.*s=\"%s\"\n", m, tmp, tmp + m + 1);
		}
	}
	free(sort_env);
	return (SUCCESS);
}

int	print_sort_env(t_mini *mini)
{
	size_t	i;
	size_t	j;
	char	*tmp;
	char	**sort_env;

	if (init_mass(&sort_env, mini->env))
		return (ERROR);
	i = 0;
	j = -1;
	while (sort_env[++j])
	{
		while (sort_env[++i])
		{
			if (ft_strcmp(sort_env[j], sort_env[i]) < 0)
			{
				tmp = sort_env[j];
				sort_env[j] = sort_env[i];
				sort_env[i] = tmp;
			}
		}
		i = j + 1;
	}
	return (print_export(sort_env));
}
