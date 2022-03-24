/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:19:27 by tharland          #+#    #+#             */
/*   Updated: 2022/03/21 15:19:29 by tharland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	sub_dollar5(t_mini *mini, size_t i, char *tmp)
{
	char	*dest;

	dest = ft_strjoin(tmp, ((char *)mini->pars->chunk->content) + i);
	if (!dest)
		return (error_mess("malloc"));
	free(tmp);
	free(((char *)mini->pars->chunk->content));
	mini->pars->chunk->content = dest;
	return (SUCCESS);
}

static int	sub_dollar4(t_mini *mini, size_t i, size_t j, char *tmp)
{
	char	*dest;
	size_t	k;
	size_t	m;

	k = 0;
	while (mini->env[k])
	{
		m = ft_findchr(mini->env[k], '=');
		if (!ft_strncmp(mini->env[k], (mini->pars->chunk->content) + j, m)
			&& ft_findchr(mini->env[k], '=') == (int)(i - j))
		{
			dest = ft_strjoin(tmp, mini->env[k] + i - j + 1);
			free(tmp);
			tmp = ft_strjoin(dest, ((char *)mini->pars->chunk->content) + i);
			if (!tmp || !dest)
				return (error_mess("malloc"));
			free(dest);
			free(((char *)mini->pars->chunk->content));
			mini->pars->chunk->content = tmp;
			return (SUCCESS);
		}
		k++;
	}
	return (sub_dollar5(mini, i, tmp));
}

static int	sub_dollar3(t_mini *mini, size_t *i)
{
	char	*tmp;
	size_t	j;
	size_t	k;

	if (!check_char(((char *)mini->pars->chunk->content)[*i + 1]))
	{
		(*i)++;
		return (SUCCESS);
	}
	k = *i;
	tmp = malloc(sizeof(char) * (k + 1));
	if (!tmp)
		return (error_mess("malloc"));
	tmp[k] = '\0';
	ft_strlcpy(tmp, mini->pars->chunk->content, k + 1);
	k++;
	j = k;
	while (check_char(((char *)mini->pars->chunk->content)[k]))
		k++;
	if (!ft_strncmp(((char *)mini->pars->chunk->content) + j, "?", 1))
		return (question_mark(mini, j, tmp));
	return (sub_dollar4(mini, k, j, tmp));
}

static int	sub_dollar1(t_mini *mini)
{
	size_t	i;
	int		flag;
	char	*str;

	flag = 2;
	i = 0;
	str = (char *)mini->pars->chunk->content;
	while (str[i])
	{
		dollar_quotes(&flag, str[i]);
		if (str[i] == '$' && flag != 1)
		{
			if (sub_dollar3(mini, &i))
				return (ERROR);
			str = (char *)mini->pars->chunk->content;
			if (ft_strlen(str) <= i)
				return (SUCCESS);
		}
		i++;
	}
	return (SUCCESS);
}

int	ft_dollar(t_mini *mini)
{
	while (mini->pars)
	{
		mini->pars->chunk = mini->pars->head_chunk;
		while (mini->pars->chunk)
		{
			if (sub_dollar1(mini))
				return (ERROR);
			mini->pars->chunk = mini->pars->chunk->next;
		}
		mini->pars->chunk = mini->pars->head_chunk;
		mini->pars = mini->pars->next;
	}
	mini->pars = mini->head_pars;
	return (SUCCESS);
}
