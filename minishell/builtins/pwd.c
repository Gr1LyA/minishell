#include "../minishell.h"

int ft_pwd(void)
{
    char str[PATH_MAX];
    
    if (getcwd(str, PATH_MAX))
    {
        ft_putstr_fd(str, STDOUT);
        ft_putstr_fd("\n", STDOUT);
        return (SUCCESS);
    }
    return (ERROR);
}