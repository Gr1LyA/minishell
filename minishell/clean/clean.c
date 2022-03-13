#include "../minishell.h"
#include <stddef.h>

static void	ft_del_lst(void *content)
{
	free(content);
}

void    ft_clean(t_mini *mini)
{
    void    *tmp;
    size_t  i;

    free(mini->path);
    while (mini->head_pars)
    {
        if (mini->head_pars->head_chunk)
            ft_lstclear(&(mini->head_pars->head_chunk), ft_del_lst);
        while (mini->head_pars->head_red)
        {
            free(mini->head_pars->head_red->name);
            tmp = mini->head_pars->head_red;
            mini->head_pars->head_red = mini->head_pars->head_red->next;
            free(tmp);
        }
        if (mini->head_pars->arg)
        {
            i = 0;
            while (mini->head_pars->arg[i])
            {
                free(mini->head_pars->arg[i]);
                i++;
            }
            free(mini->head_pars->arg);
        }
        tmp = mini->head_pars;
        mini->head_pars = mini->head_pars->next;
        free(tmp);
    }
    // close(STDIN);
    // close(STDOUT);
    dup2(mini->in, STDIN);
    dup2(mini->out, STDOUT);
}