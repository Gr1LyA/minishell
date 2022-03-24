/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:19:09 by tharland          #+#    #+#             */
/*   Updated: 2022/03/21 15:19:10 by tharland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_fork_error(t_mini *mini)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(mini->pars->arg[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	exit (ERROR);
}

void	ft_fork(t_mini *mini)
{
	char	*path;
	int		ret;

	signal(SIGINT, SIG_DFL);
	if (mini->which_close != -1)
		close(mini->which_close);
	if (redir(mini))
		exit (ERROR);
	ret = builtin(mini);
	if (ret != -1)
		exit (ret);
	if (!mini->pars->arg[0])
		exit (SUCCESS);
	if (!ft_strncmp(mini->pars->arg[0], "./", 2)
		|| !ft_strncmp(mini->pars->arg[0], "../", 3)
		|| !ft_strncmp(mini->pars->arg[0], "/", 1))
	{
		execve(mini->pars->arg[0], mini->pars->arg, mini->env);
		exit (error_mess(mini->pars->arg[0]));
	}
	path = find_path(ft_strjoin("/", mini->pars->arg[0]), mini->path);
	if (!path)
		ft_fork_error(mini);
	execve(path, mini->pars->arg, mini->env);
	exit (error_mess(mini->pars->arg[0]));
}

void	wait_daughter(t_mini *mini, pid_t *pid, size_t i)
{
	size_t	j;

	dup2(mini->in, STDIN);
	j = 0;
	while (j < i)
	{
		waitpid(pid[j], &(mini->status), 0);
		j++;
		if (WIFEXITED(mini->status))
			mini->status = WEXITSTATUS(mini->status);
		else if (WIFSIGNALED(mini->status))
			mini->status = WTERMSIG(mini->status) + 128;
	}
	free(pid);
}

void	ft_pipe(size_t num_pipe, size_t i, t_mini *mini)
{
	if (i == 0)
	{
		pipe(mini->fd);
		dup2(mini->fd[1], STDOUT);
		close(mini->fd[1]);
		mini->which_close = mini->fd[0];
	}
	else if (i < num_pipe)
	{
		dup2(mini->fd[0], STDIN);
		close(mini->fd[0]);
		close(mini->fd[1]);
		pipe(mini->fd);
		dup2(mini->fd[1], STDOUT);
		close(mini->fd[1]);
		mini->which_close = mini->fd[0];
	}
	else if (i == num_pipe)
	{
		dup2(mini->fd[0], STDIN);
		close(mini->fd[0]);
		dup2(mini->out, STDOUT);
		mini->which_close = -1;
	}
}

int	executor(t_mini *mini)
{
	size_t	num_pipe;
	size_t	i;
	pid_t	*pid;
	int		ret;

	signal(SIGINT, main_sig2);
	num_pipe = check_pipe(mini);
	ret = check_builtin(mini, num_pipe);
	if (ret == 0 || ret == 1)
		return (ret);
	pid = malloc(sizeof(pid_t) * (num_pipe + 1));
	i = 0;
	while (mini->pars)
	{
		if (num_pipe != 0)
			ft_pipe(num_pipe, i, mini);
		pid[i] = fork();
		if (pid[i] == 0)
			ft_fork(mini);
		else if (pid[i++] < 0)
			return (error_mess("fork"));
		mini->pars = mini->pars->next;
	}
	wait_daughter(mini, pid, i);
	return (SUCCESS);
}
