/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:19:37 by tharland          #+#    #+#             */
/*   Updated: 2022/03/21 15:19:39 by tharland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parser(char *line, t_mini *mini)
{
	if (split_line(line, mini))
		return (ERROR);
	if (ft_dollar(mini))
		return (ERROR);
	if (ft_redir(mini))
		return (ERROR);
	if (ft_dest_arg(mini))
		return (ERROR);
	if (ft_quote(mini))
		return (ERROR);
	return (SUCCESS);
}
