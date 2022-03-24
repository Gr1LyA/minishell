/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:51:21 by tharland          #+#    #+#             */
/*   Updated: 2022/03/21 15:51:22 by tharland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_for_redir(t_mini *mini, char *cmd)
{
	int	flag;

	flag = 1;
	if (!ft_strncmp("echo", cmd, ft_strlen(cmd)))
		flag = 0;
	else if (!ft_strncmp("cd", cmd, ft_strlen(cmd)))
		flag = 0;
	else if (!ft_strncmp("env", cmd, ft_strlen(cmd)))
		flag = 0;
	else if (!ft_strncmp("pwd", cmd, ft_strlen(cmd)))
		flag = 0;
	else if (!ft_strncmp("export", cmd, ft_strlen(cmd)))
		flag = 0;
	else if (!ft_strncmp("unset", cmd, ft_strlen(cmd)))
		flag = 0;
	else if (!ft_strncmp("exit", cmd, ft_strlen(cmd)))
		flag = 0;
	if (flag == 0)
	{
		if (redir(mini))
			return (ERROR);
	}
	return (SUCCESS);
}

int	builtin(t_mini *mini)
{
	char	*cmd;

	if (!mini->pars)
		return (-1);
	if (!mini->pars->arg[0])
		return (-1);
	cmd = mini->pars->arg[0];
	if (check_for_redir(mini, cmd))
		return (ERROR);
	if (!ft_strncmp("echo", cmd, ft_strlen(cmd)))
		return (ft_echo(mini->pars->arg));
	else if (!ft_strncmp("cd", cmd, ft_strlen(cmd)))
		return (ft_cd(mini, mini->pars->arg[1]));
	else if (!ft_strncmp("env", cmd, ft_strlen(cmd)))
		return (ft_env(mini->env));
	else if (!ft_strncmp("pwd", cmd, ft_strlen(cmd)))
		return (ft_pwd());
	else if (!ft_strncmp("export", cmd, ft_strlen(cmd)))
		return (ft_export(mini));
	else if (!ft_strncmp("unset", cmd, ft_strlen(cmd)))
		return (ft_unset(mini));
	else if (!ft_strncmp("exit", cmd, ft_strlen(cmd)))
		return (ft_exit(mini));
	else
		return (-1);
}

int	check_builtin(t_mini *mini, size_t num_pipe)
{
	int	ret;

	ret = -1;
	if (num_pipe == 0)
	{
		ret = builtin(mini);
		if (ret == 0 || ret == 1)
			mini->status = ret;
	}
	return (ret);
}
