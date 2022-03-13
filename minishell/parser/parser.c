#include "../minishell.h"

// void check_print(t_mini *mini)
// {
// 	size_t i;

// 	while (mini->pars)
// 	{
// 		i = 0;
// 		printf("\n\n------arg-----\n");
// 		while (mini->pars->arg[i])
// 		{
// 			printf("'%s'\n", mini->pars->arg[i]);
// 			i++;
// 		}
// 		printf("------redirect-----\n");	
// 		while (mini->pars->red)
// 		{
// 			printf("%s\n", mini->pars->red->name);
// 			mini->pars->red = mini->pars->red->next;
// 		}
// 		mini->pars->red = mini->pars->head_red;
// 		mini->pars = mini->pars->next;
// 	}
// 	mini->pars = mini->head_pars;
// }

int	parser(char *line, t_mini *mini)
{
	if (split_line(line, mini))//ошибка толкьо при маллок или неккорректный пайп
		return (ERROR);
	if (ft_dollar(mini))//
		return (ERROR);
	if (ft_redir(mini))//тут заполняю редиректы
		return (ERROR);
	if (ft_dest_arg(mini))//тут заполняю массив arg
		return (ERROR);
	if (ft_quote(mini))
		return (ERROR);
	// check_print(mini);//вывожу на экран для проверки
	return (SUCCESS);
}