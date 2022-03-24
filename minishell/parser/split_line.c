/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:19:55 by tharland          #+#    #+#             */
/*   Updated: 2022/03/21 15:20:04 by tharland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	split_line3(t_mini *mini, char **str, size_t i)
{
	if (*str == NULL)
		return (ERROR);
	if (i == 0)
	{
		mini->pars->chunk = ft_lstnew(*str);
		mini->pars->head_chunk = mini->pars->chunk;
	}
	else
	{
		mini->pars->chunk->next = ft_lstnew(*str);
		mini->pars->chunk = mini->pars->chunk->next;
	}
	if (!mini->pars->chunk)
		return (ERROR);
	mini->pars->chunk->next = NULL;
	return (-1);
}

int	split_line2(char **line, t_mini *mini, size_t *i, size_t *j)
{
	if (**line == '\0' && *i == 0 && *j == 0)
		return (SUCCESS);
	else if (*i == 0 && *j == 0 && **line)
	{
		mini->pars = init_pars();
		if (!mini->pars)
			return (ERROR);
		mini->head_pars = mini->pars;
	}
	if (**line == '|' && *i != 0)
	{
		(*line)++;
		while (**line == ' ' || (**line > 9 && **line < 13))
			(*line)++;
		if (!**line)
			return (ERROR);
		*i = 0;
		mini->pars->chunk = mini->pars->head_chunk;
		mini->pars->next = init_pars();
		if (!mini->pars->next)
			return (ERROR);
		mini->pars = mini->pars->next;
		(*j)++;
	}
	return (-1);
}

int	split_line(char *line, t_mini *mini)
{
	char	*str;
	size_t	i;
	size_t	j;
	int		ret;

	i = 0;
	j = 0;
	while (*line)
	{
		while (*line == ' ' || (*line > 9 && *line < 13))
			line++;
		ret = split_line2(&line, mini, &i, &j);
		if (ret != -1)
			return (ret);
		if (*line == '|' && i == 0)
			return (ERROR);
		str = sub_split_line(&line);
		ret = split_line3(mini, &str, i);
		if (ret != -1)
			return (ret);
		while (*line == ' ' || (*line > 9 && *line < 13))
			line++;
		i++;
	}
	return (SUCCESS);
}
