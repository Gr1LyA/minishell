#include "../minishell.h"
#include <stddef.h>

size_t check_pipe(t_mini *mini)
{
    size_t  i;

    i = 0;
    while (mini->pars->next)
    {
        i++;
        mini->pars = mini->pars->next;
    }
    mini->pars = mini->head_pars;
    return (i);
}

char *find_path(char *cmd, char *path)
{
    char    **path_split;
    size_t  i;
    char    *ret;
    char    *tmp;

    if (!path)
        return (NULL);
    path_split = ft_split(path, ':');
    i = 0;
    while (path_split[i])
    {
        tmp = path_split[i];
        path_split[i] = ft_strjoin(path_split[i], cmd);
        free(tmp);
        i++;
    }
    free(cmd);
    i = 0;
    while (access(path_split[i], 1) != 0 && path_split[i])
        i++;
    // printf("path = %s | %zu\n", path_split[i],  i);
    if (!path_split[i])
    {
        i = 0;
         while (path_split[i])
            free(path_split[i++]);
        free(path_split);
        return (NULL);
    }
    ret = ft_strdup(path_split[i]);
    i = 0;
    while (path_split[i])
        free(path_split[i++]);
    free(path_split);
    return (ret);
}

int check_redir(int type, char *name)//че то не так !!!!!!!!!!!!!!!!!!!!!!!!
{
    // printf("name = %s, type = %d\n", name, type);
    int fd;
    char *error_mess;

    fd = -1;
    error_mess = ft_strjoin("minishell: ", name);
    // printf("file = %s\n")
    if (type == RIGHT)
    {
        // close(STDOUT);
        fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0664);
        if (fd == -1)
            perror(error_mess);
        else
        {
            dup2(fd, STDOUT);
            close(fd);
        }
    }
    else if (type == D_RIGHT)
    {
        // close(STDOUT);
        fd = open(name, O_WRONLY | O_CREAT | O_APPEND, 0664);
        if (fd == -1)
            perror(error_mess);
        else
            dup2(fd, STDOUT);
    }
    else if (type == LEFT)
    {
        // close(STDIN);
        fd = open(name, O_RDONLY, 0664);
        if (fd == -1)
            perror(error_mess);
        else
            dup2(fd, STDIN);
    }
    // else if (type == RIGHT)
    // {
        
    // }
    free(error_mess);
    if (fd == -1)
        return (ERROR);
    return (SUCCESS);
}

int redir(t_mini *mini)
{
    while (mini->pars->red)
    {
        if (check_redir(mini->pars->red->type, mini->pars->red->name))
            return (ERROR);
        mini->pars->red = mini->pars->red->next;
    }
    mini->pars->red = mini->pars->head_red;
    return (SUCCESS);
}

void ft_fork(t_mini *mini)
{
    char    *path;

    // ft_signal_def();
    if (mini->which_close != -1)
        close(mini->fd[mini->which_close]);
    if (redir(mini))
        exit (ERROR);
    if (!mini->pars->arg[0])
        exit (SUCCESS);
    execve(mini->pars->arg[0], mini->pars->arg, mini->env);//для абсолютного пути
    path = find_path(ft_strjoin("/", mini->pars->arg[0]), mini->path);
    if (!path)
    {
        printf("minishell: %s: command not found\n", mini->pars->arg[0]);//поменять на write вывод в stderror
        exit (ERROR);
    }
    execve(path, mini->pars->arg, mini->env);
    // exit (ERROR);
    // return (ERROR);
}

void    wait_daughter(t_mini *mini, pid_t *pid, size_t i)
{
    size_t j;

    j = 0;
    while (j < i)//ожидаю дочек по очереди
    {
        waitpid(pid[j], &(mini->status), 0);
        // printf("j = %zu\n", j);
        j++;
    }
    free(pid);
}

void    ft_pipe(size_t num_pipe, size_t i, t_mini *mini)//три варианта: если команда первая, последняя и в промежутке
{
    // printf("i = %zu\n", i);
    if (i == 0)//если первая
    {
        pipe(mini->fd);//Создается пайп (2 фд)
        dup2(mini->fd[1], STDOUT);//Перенаправляется стдоут  и закрывается фд1 (1д)
        close(mini->fd[1]);
        mini->which_close = 0;//в форке закрываю fd[0]
    }
    else if (i < num_pipe)//если в промежутке
    {
        dup2(mini->fd[0], STDIN);
        close(mini->fd[0]);//если убрать то yes | head | ps виснет
        close(mini->fd[1]);
        pipe(mini->fd);
        dup2(mini->fd[1], STDOUT);
        close(mini->fd[1]);
        mini->which_close = 0;//в форке закрываю fd[0]
    }
    else if (i == num_pipe)//если последняя команда
    {
        dup2(mini->fd[0], STDIN);//Перенаправляется стдин в фд0
        close(mini->fd[0]);//Закрывается фд0
        // close(mini->fd[1]);
        dup2(mini->out, STDOUT);//Востанавливается стдаут
        mini->which_close = -1;//в форке ничего не закрываю
        // printf("HI\n");
    }
    // printf("i = %zu\n", i);
}

int executor(t_mini *mini)
{
    size_t  num_pipe;//кол-во пайпов
    size_t  i;
    pid_t   *pid;

    num_pipe = check_pipe(mini);//num of pipe
    // printf("num_pipe = %zu\n", num_pipe);
    pid = malloc(sizeof(pid_t) * (num_pipe + 1));
    i = 0;
    while (mini->pars)
    {
        if (num_pipe != 0)
            ft_pipe(num_pipe, i, mini);
        pid[i] = fork();
        if (pid[i] == 0)
            ft_fork(mini);
        else if (pid[i] < 0)
            return (ERROR);
        mini->pars = mini->pars->next;
        i++;
    }
    // printf("HIII\n");
    wait_daughter(mini, pid, i);
        // printf("YOO\n");

    mini->pars = mini->head_pars;
    return (SUCCESS);
}