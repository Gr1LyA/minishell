#include "minishell.h"
#include <signal.h>
#include <stddef.h>

void check_print(t_mini *mini)
{
	size_t i;

	while (mini->pars)
	{
		i = 0;
		printf("\n\n------arg-----\n");
		while (mini->pars->arg[i])
		{
			printf("'%s'\n", mini->pars->arg[i]);
			i++;
		}
		printf("------redirect-----\n");	
		while (mini->pars->red)
		{
			printf("%s\n", mini->pars->red->name);
			mini->pars->red = mini->pars->red->next;
		}
		mini->pars->red = mini->pars->head_red;
		mini->pars = mini->pars->next;
	}
	mini->pars = mini->head_pars;
}

void	main_sig(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		rl_redisplay();
		write(1, "  \b\b\n", 5);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void ft_signal(void)
{
	signal(SIGINT, main_sig);
	signal(SIGQUIT, SIG_IGN);
}

void ft_signal_def(void)//запустить в форке
{
	// signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

int main(int argc, char **argv, char **envp)
{
    char    *line;
    t_mini  mini;

	mini.in = dup(STDIN);
    mini.out = dup(STDOUT);
	mini.status = 0;
    (void)argc;
    (void)argv;
	if (get_env(&mini, envp))
        return (ERROR);
    while (1)
    {
		ft_signal();
        if (init_mini(&mini))
            return (ERROR);
        line = readline("minishell> ");
		if (!line)
			exit(0);
        add_history(line);
        parser(line, &mini);
        
    	// check_print(&mini);//вывожу на экран для проверки
        // exit (0);
        
        free(line);
		ft_signal_def();
        executor(&mini);
        ft_clean(&mini);
		// dup2(mini.in, STDIN);
	    // dup2(mini.out, STDOUT);
    }
    return (SUCCESS);
}

// ___________________________________________________________________________________________________
                                            // check
// ___________________________________________________________________________________________________
// int main(int argc, char **argv, char **envp)
// {
//     // char    line[] = "'asd'";
//     char    line[] = "yes | head";
//     // char    line[] = "'asd'>aa'a''$>$";
//     // char    line[] = "'asd'>aa'a''$>$";
//     // char    line[] = "'asd'>aa'a''$>$";

//     t_mini  mini;
//     size_t  i;

//     (void)argc;
//     (void)argv;
// 		mini.in = dup(STDIN);
//     mini.out = dup(STDOUT);
// 	if (get_env(&mini, envp))
//         return (ERROR);
//     while (1)
//     {
//         if (init_mini(&mini))//заношу в структуру path пути и env
//             return (ERROR);
//         parser(line, &mini);
//         executor(&mini);
//         i = 0;
//         while (mini.env[i])
//         {
//             free(mini.env[i]);
//             i++;
//         }
//         free(mini.env);
//         ft_clean(&mini);


//         exit (0);
//     }
//     return (SUCCESS);
// }