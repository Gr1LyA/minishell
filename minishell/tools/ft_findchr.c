#include "../minishell.h"

size_t  ft_findchr(char *str, char ch)
{
    size_t  i;

    i = 0;
    while (str[i] && str[i] != ch)
        i++;
    return (i);
}