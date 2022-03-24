/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:17:51 by tharland          #+#    #+#             */
/*   Updated: 2022/03/21 15:17:54 by tharland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	main_sig2(int sig)
{
	if (sig == SIGINT)
		write(1, "\n", 1);
}

static void	main_sig(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		rl_redisplay();
		write(1, "  \b\b\n", 5);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	ft_signal(void)
{
	signal(SIGINT, main_sig);
	signal(SIGQUIT, SIG_IGN);
}

int	ctrl_d(t_mini *mini)
{
	clean_env(mini);
	write (1, "exit\n", 5);
	ft_clean(mini);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_mini	mini;

	mini.in = dup(STDIN);
	mini.out = dup(STDOUT);
	(void)argc;
	(void)argv;
	mini.status = 0;
	if (init_env(&mini, envp))
		return (ERROR);
	while (1)
	{
		ft_signal();
		if (init_mini(&mini))
			return (ERROR);
		line = readline("minishell> ");
		if (!line)
			return (ctrl_d(&mini));
		add_history(line);
		if (!parser(line, &mini))
			executor(&mini);
		free(line);
		ft_clean(&mini);
	}
	return (SUCCESS);
}
