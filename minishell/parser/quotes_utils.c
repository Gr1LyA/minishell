/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:19:46 by tharland          #+#    #+#             */
/*   Updated: 2022/03/21 15:19:48 by tharland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	sub_quotes2(char **str, size_t *i, size_t j)
{
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;

	tmp1 = ft_strndup(*str, j - 1);
	tmp2 = ft_strndup((*str) + j, *i - j);
	tmp3 = ft_strjoin(tmp1, tmp2);
	if (!tmp3 || !tmp2 || !tmp1)
		return (error_mess("malloc"));
	free(tmp1);
	free(tmp2);
	tmp1 = *str;
	*str = ft_strjoin(tmp3, ((*str) + *i + 1));
	if (!*str)
		return (error_mess("malloc"));
	free(tmp1);
	free(tmp3);
	*i -= 2;
	return (SUCCESS);
}

static int	sub_quotes(char **str, size_t *i)
{
	int		flag;
	size_t	j;

	if ((*str)[*i] == '"')
		flag = 0;
	else if ((*str)[*i] == '\'')
		flag = 1;
	else
		return (SUCCESS);
	(*i)++;
	j = (*i);
	while ((((*str)[*i] != '\'' && flag == 1)
		|| ((*str)[*i] != '"' && flag == 0)) && (*str)[*i])
		(*i)++;
	if (!(*str)[*i])
		return (ERROR);
	return (sub_quotes2(str, i, j));
}

static int	quotes(char **str)
{
	size_t	i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '"' || (*str)[i] == '\'')
		{
			if (sub_quotes(str, &i))
				return (ERROR);
		}
		i++;
	}
	return (SUCCESS);
}

int	ft_quotes_red(t_red *red)
{
	while (red)
	{
		if (quotes(&red->name))
			return (ERROR);
		red = red->next;
	}
	return (SUCCESS);
}

int	ft_quotes_arg(t_pars *pars)
{
	size_t	i;

	i = 0;
	while (pars->arg[i])
	{
		if (quotes(pars->arg + i))
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}
