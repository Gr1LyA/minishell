#include "../minishell.h"

void    ft_env(char **env)
{
    size_t i;

    i = 0;
    while (env[i])
    {
        ft_putstr_fd(env[i], STDOUT);
        ft_putstr_fd("\n", STDOUT);
        i++;
    }
}