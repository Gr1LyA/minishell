#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <errno.h>
# include "libft/libft.h"
# include <stddef.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>

# define STDIN 0
# define STDOUT 1
# define STRERR 2

# define ERROR 1
# define SUCCESS 0

# define RIGHT 0
# define D_RIGHT 1
# define LEFT 2
# define D_LEFT 3

// # define CMD 4
// # define ARG 5

typedef struct		s_red
{
	int				type;
	char			*name;
	struct s_red	*next;
}					t_red;

typedef struct 			s_pars
{
	
	// int					type;
	t_list				*head_chunk;//голова списка head
	t_list				*chunk;
	t_red				*head_red;
	t_red				*red;
	char				**arg;//аргументы и команда
	struct s_pars		*next;
}						t_pars;

typedef struct s_mini
{
	int			in;
	int			out;
	int			status;
	int			fd[2];
	int			which_close;
	// int			fd_zero;
	char		**env;//переменные окружения
	char		*path;
	t_pars		*head_pars;//голова списка pars
	t_pars		*pars;
}				t_mini;

void    ft_echo(char **str);
int     ft_pwd(void);
void    ft_env(char **env);
int		get_env(t_mini *mini, char **envp);//перености переменные окружения в массив структуры(чтоб можно было его изменять)
int 	get_path(t_mini *mini);
size_t 	ft_findchr(char *str, char ch);
int 	split_line(char *line, t_mini *mini);
int 	init_mini(t_mini *mini);
t_pars	*init_pars(void);
int		parser(char *line, t_mini *mini);
char    *ft_strndup(const char *str, size_t len);
void	ft_clean(t_mini *mini);
int 	ft_dest_arg(t_mini *mini);
int 	ft_dollar(t_mini *mini);
int 	ft_redir(t_mini *mini);
int		ft_quote(t_mini *mini);
int		executor(t_mini *mini);
void	ft_signal_def(void);

#endif