/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:19:27 by tharland          #+#    #+#             */
/*   Updated: 2022/03/21 15:19:29 by tharland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_char(char ch)
{
	if (!ch || ch == '"' || ch == '\'' || ch == '>'
		|| ch == '<' || ch == '|' || ch == ' '
		|| (ch > 9 && ch < 13) || ch == '$')
		return (0);
	return (1);
}

void	dollar_quotes(int *flag, char c)
{
	if (c == '"' && *flag == 2)
		*flag = 0;
	else if (c == '"' && *flag == 0)
		*flag = 2;
	if (c == '\'' && *flag == 2)
		*flag = 1;
	else if (c == '\'' && *flag == 1)
		*flag = 2;
}

int	question_mark(t_mini *mini, size_t j, char *tmp)
{
	char	*tmp1;
	char	*dest;

	tmp1 = ft_itoa(mini->status);
	dest = ft_strjoin(tmp, tmp1);
	if (!dest || !tmp1)
		return (error_mess("malloc"));
	free(tmp1);
	free(tmp);
	tmp1 = ft_strjoin(dest, (char *)mini->pars->chunk->content + j + 1);
	if (!tmp1)
		return (error_mess("malloc"));
	free(mini->pars->chunk->content);
	free(dest);
	mini->pars->chunk->content = tmp1;
	return (SUCCESS);
}
