/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_split_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:19:55 by tharland          #+#    #+#             */
/*   Updated: 2022/03/21 15:20:04 by tharland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_quotes(char *line)
{
	size_t	i;
	int		flag;

	i = 1;
	if (*line == '\'')
		flag = 0;
	else if (*line == '"')
		flag = 1;
	while (((line[i] != '"' && flag == 1)
			|| (line[i] != '\'' && flag == 0)) && line[i])
		i++;
	if (!line[i])
		return (i - 1);
	return (i);
}

static int	ft_red(char **line)
{
	size_t	i;

	i = 1;
	while ((*line)[i] && ((*line)[i] == '>' || (*line)[i] == '<'
		|| ((*line)[i] > 9 && (*line)[i] < 13) || (*line)[i] == ' '))
	{
		if ((*line)[i] == '\'' || (*line)[i] == '"')
			i += (ft_quotes((*line) + i));
		i++;
	}
	while ((*line)[i] && (*line)[i] != '|')
	{
		if ((*line)[i] == '\'' || (*line)[i] == '"')
			i += (ft_quotes((*line) + i));
		if (((*line)[i] == '>' || (*line)[i] == '<'
			|| ((*line)[i] > 9 && (*line)[i] < 13) || (*line)[i] == ' '))
			break ;
		i++;
	}
	return (i);
}

char	*sub_split_line(char **line)
{
	size_t	i;
	char	*str;

	i = 0;
	while ((*line)[i])
	{
		if (((*line)[i] == ' ' || ((*line)[i] > 9 && (*line)[i] < 13)))
			break ;
		if ((*line)[i] == '\'' || (*line)[i] == '"')
			i += (ft_quotes((*line) + i));
		if (((*line)[i] == '>' || (*line)[i] == '<') && i == 0)
		{
			i += ft_red(line);
			break ;
		}
		else if (((*line)[i] == '>' || (*line)[i] == '<') && i != 0)
			break ;
		i++;
		if ((*line)[i] == '|')
			break ;
	}
	str = ft_strndup(*line, i);
	*line += i;
	return (str);
}
