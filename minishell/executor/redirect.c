/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:51:21 by tharland          #+#    #+#             */
/*   Updated: 2022/03/21 15:51:22 by tharland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	heredoc(char *name, t_mini *mini)
{
	int		fd;
	char	*str;

	dup2(mini->in, STDIN);
	fd = open("tools/heredoc.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
		return (ERROR);
	str = readline("> ");
	if (!str)
		return (SUCCESS);
	while (ft_strncmp(str, name, ft_strlen(str) + 1))
	{
		if (!str)
			return (SUCCESS);
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		free(str);
		str = readline("> ");
		if (!str)
			return (SUCCESS);
	}
	free(str);
	signal(SIGINT, SIG_DFL);
	close(fd);
	return (SUCCESS);
}

static void	check_redir2(int type, char *name, int *fd, t_mini *mini)
{
	if (type == LEFT)
	{
		*fd = open(name, O_RDONLY, 0664);
		if (*fd == -1)
			error_mess(name);
		else
			dup2(*fd, STDIN);
	}
	if (type == D_LEFT)
	{
		signal(SIGQUIT, SIG_IGN);
		if (heredoc(name, mini))
			error_mess(name);
		else
		{
			*fd = open("tools/heredoc.txt", O_RDONLY);
			if (*fd == -1)
				error_mess(name);
			else
				dup2(*fd, STDIN);
		}
	}
}

static int	check_redir(int type, char *name, t_mini *mini)
{
	int	fd;

	fd = -1;
	if (type == RIGHT)
	{
		fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0664);
		if (fd == -1)
			error_mess(name);
		else
			dup2(fd, STDOUT);
	}
	else if (type == D_RIGHT)
	{
		fd = open(name, O_WRONLY | O_CREAT | O_APPEND, 0664);
		if (fd == -1)
			error_mess(name);
		else
			dup2(fd, STDOUT);
	}
	check_redir2(type, name, &fd, mini);
	close(fd);
	if (fd == -1)
		return (ERROR);
	return (SUCCESS);
}

int	redir(t_mini *mini)
{
	while (mini->pars->red)
	{
		if (check_redir(mini->pars->red->type, mini->pars->red->name, mini))
			return (ERROR);
		mini->pars->red = mini->pars->red->next;
	}
	mini->pars->red = mini->pars->head_red;
	return (SUCCESS);
}
