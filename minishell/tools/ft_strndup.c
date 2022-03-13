#include "../minishell.h"

char    *ft_strndup(const char *str, size_t len)
{
    char *ret;

    ret = malloc(sizeof(char) * len + 1);
    if (!ret)
        return (NULL);
    ret[len] = '\0';
    ft_strlcpy(ret, str, len + 1);
    return (ret);
}