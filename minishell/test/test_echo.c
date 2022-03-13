#include "../minishell.h"

// gcc test/test_echo.c builtins/echo.c -L libft -lft


int main()
{
    char *str[]={"-n", "a", "asd", 0};

    ft_echo(str);
}