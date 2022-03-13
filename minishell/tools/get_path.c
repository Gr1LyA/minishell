#include "../minishell.h"

int get_path(t_mini *mini)//проверить
{
	size_t i;

	i = 0;
	// if (!mini->env)
	// 	return (ERROR);
	while (mini->env[i])
	{
		if (!ft_strncmp("PATH=", mini->env[i], 5))
		{
			mini->path = ft_strdup(mini->env[i] + 5);
			if (!mini->path)
				return (ERROR);
			return (SUCCESS);
		}
		i++;
	}
	mini->path = NULL;//если path удалили из env
	return (SUCCESS);
}