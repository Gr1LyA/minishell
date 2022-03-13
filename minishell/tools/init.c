#include "../minishell.h"

t_pars *init_pars(void)
{
	t_pars *pars;

	pars = malloc(sizeof(t_pars));
	if (!pars)
		return (NULL);
	pars->next = NULL;
	pars->arg = NULL;
	pars->red = NULL;
	pars->head_red = NULL;
	pars->chunk = NULL;
	pars->head_chunk = NULL;
	return (pars);
}
int init_mini(t_mini *mini)
{
	mini->which_close = -1;
	mini->pars = NULL;
	mini->head_pars = NULL;//заполняю голову списка парс
    if (get_path(mini))
	{
        return (ERROR);
	}
	return (SUCCESS);
}
