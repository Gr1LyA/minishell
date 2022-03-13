#include "../minishell.h"

// gcc test/test_env.c builtins/env.c -L libft -lft

int main(int argc, char **argv, char **env)
{
    ft_env(env);
}