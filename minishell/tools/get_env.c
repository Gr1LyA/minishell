#include "../minishell.h"

int	get_env(t_mini *mini, char **envp)
{
	size_t i;

	i = 0;
	while (envp[i])
		i++;
	mini->env = malloc(sizeof(char*) * (i + 1));
	if (!(mini->env))
		return (ERROR);
	i = 0;
	while (envp[i])
	{
		mini->env[i] = ft_strdup(envp[i]);
		if (!(mini->env[i]))
			return (ERROR);
		i++;
	}
	mini->env[i] = NULL;
	return (SUCCESS);
}