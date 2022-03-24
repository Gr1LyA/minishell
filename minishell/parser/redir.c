/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:19:55 by tharland          #+#    #+#             */
/*   Updated: 2022/03/21 15:20:04 by tharland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	type_red(char **str, t_red *red)
{
	if (!ft_strncmp(*str, ">>", 2))
	{
		red->type = D_RIGHT;
		*str += 2;
	}
	else if (!ft_strncmp(*str, "<<", 2))
	{
		red->type = D_LEFT;
		*str += 2;
	}
	else if (!ft_strncmp(*str, ">", 1))
	{
		red->type = RIGHT;
		*str += 1;
	}
	else if (!ft_strncmp(*str, "<", 1))
	{
		red->type = LEFT;
		*str += 1;
	}
	else
		return (ERROR);
	return (SUCCESS);
}

int	pars_red(char *str, t_red *red)
{
	if (type_red(&str, red))
		return (ERROR);
	while (*str == ' ' || (*str > 9 && *str < 13))
		str++;
	if (*str == '>' || *str == '<' || !*str)
		return (ERROR);
	red->name = ft_strndup(str, ft_strlen(str));
	if (!red->name)
		return (ERROR);
	return (SUCCESS);
}

int	sub_ft_dest_red(t_mini *mini, size_t i)
{
	if (i == 0)
	{
		mini->pars->red = malloc(sizeof(t_red));
		if (!mini->pars->red)
			return (ERROR);
		mini->pars->head_red = mini->pars->red;
	}
	else
	{
		mini->pars->red->next = malloc(sizeof(t_red));
		if (!mini->pars->red->next)
			return (ERROR);
		mini->pars->red = mini->pars->red->next;
	}
	mini->pars->red->name = NULL;
	mini->pars->red->next = NULL;
	return (SUCCESS);
}

int	ft_dest_red(t_mini *mini, t_list *chunk)
{
	char	*str;
	size_t	i;

	i = 0;
	while (chunk)
	{
		if (((char *)chunk->content)[0] == '<'
			|| ((char *)chunk->content)[0] == '>')
		{
			str = (char *)chunk->content;
			if (sub_ft_dest_red(mini, i))
				return (error_mess("malloc"));
			if (pars_red(str, mini->pars->red))
				return (ERROR);
			i++;
		}
		chunk = chunk->next;
	}
	mini->pars->red = mini->pars->head_red;
	return (SUCCESS);
}

int	ft_redir(t_mini *mini)
{
	while (mini->pars)
	{
		if (ft_dest_red(mini, mini->pars->chunk))
			return (ERROR);
		mini->pars = mini->pars->next;
	}
	mini->pars = mini->head_pars;
	return (SUCCESS);
}
