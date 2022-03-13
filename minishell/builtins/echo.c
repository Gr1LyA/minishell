#include "../minishell.h"

static int number_args(char **str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

void    ft_echo(char **str)
{
    int flag;
    int i;

    i = 0;
    if (number_args(str) == 0)
        return ;
    flag = ft_strncmp("-n", str[i], 3);
    if (!flag)
        i++;
    while (str[i])
    {
        ft_putstr_fd(str[i], STDOUT);
        i++;
        if (str[i])
            ft_putstr_fd(" ", STDOUT);
    }
    if (flag)
        ft_putstr_fd("\n", STDOUT);
}