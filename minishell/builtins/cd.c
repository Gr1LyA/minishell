/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:50:52 by tharland          #+#    #+#             */
/*   Updated: 2022/03/21 15:50:54 by tharland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	go_to_home(t_mini *mini)
{
	char	*home;

	home = get_env(mini, "HOME=");
	if (!home)
	{
		ft_putstr_fd("minihell: cd: HOME not set\n", 2);
		return (ERROR);
	}
	if (chdir(home))
	{
		ft_putstr_fd("minihell: cd: ", 2);
		perror(home);
		free(home);
		return (ERROR);
	}
	free(home);
	return (SUCCESS);
}

void	set_old_new_pwd(t_mini *mini, char *old)
{
	char	*pwd;

	set_env(mini, "OLDPWD", old);
	pwd = getcwd(0, 0);
	if (pwd)
		set_env(mini, "PWD", pwd);
	else
		error_mess("malloc");
	free(pwd);
	free(old);
}

int	ft_cd(t_mini *mini, char *dest)
{
	char	*old;
	int		ret;

	old = getcwd(0, 0);
	if (!old)
		return (error_mess("malloc"));
	if (!dest)
		ret = go_to_home(mini);
	else
	{
		ret = chdir(dest);
		if (ret)
		{
			free(old);
			old = ft_strjoin("cd: ", dest);
			error_mess(old);
			free(old);
			return (1);
		}
	}
	if (!ret)
		set_old_new_pwd(mini, old);
	return (ret);
}
