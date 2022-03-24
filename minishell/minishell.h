/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:18:25 by tharland          #+#    #+#             */
/*   Updated: 2022/03/21 15:18:26 by tharland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

typedef struct s_red
{
	int				type;
	char			*name;
	struct s_red	*next;
}					t_red;

typedef struct s_pars
{
	t_list			*head_chunk;
	t_list			*chunk;
	t_red			*head_red;
	t_red			*red;
	char			**arg;
	struct s_pars	*next;
}					t_pars;

typedef struct s_mini
{
	int			in;
	int			out;
	int			status;
	int			fd[2];
	int			which_close;
	char		**env;
	char		*path;
	t_pars		*head_pars;
	t_pars		*pars;
}				t_mini;

int		ft_echo(char **str);
int		ft_pwd(void);
int		ft_env(char **env);
int		init_env(t_mini *mini, char **envp);
int		get_path(t_mini *mini);
int		ft_findchr(char *str, char ch);
int		split_line(char *line, t_mini *mini);
char	*sub_split_line(char **line);
int		init_mini(t_mini *mini);
t_pars	*init_pars(void);
int		parser(char *line, t_mini *mini);
char	*ft_strndup(const char *str, size_t len);
void	ft_clean(t_mini *mini);
int		ft_dest_arg(t_mini *mini);
int		ft_dollar(t_mini *mini);
int		ft_redir(t_mini *mini);
int		ft_quote(t_mini *mini);
int		executor(t_mini *mini);
void	ft_signal_def(void);
void	main_sig2(int sig);
int		error_mess(char *str);
char	*get_env(t_mini *mini, char *str);
int		set_env(t_mini *mini, char *env, char *vol);
int		ft_cd(t_mini *mini, char *dest);
void	rl_replace_line(const char *text, int clear_undo);
void	clean_env(t_mini *mini);
int		ft_export(t_mini *mini);
int		ft_unset(t_mini *mini);
int		ft_exit(t_mini *mini);
int		print_sort_env(t_mini *mini);
char	*find_path(char *cmd, char *path);
size_t	check_pipe(t_mini *mini);
int		check_builtin(t_mini *mini, size_t num_pipe);
int		builtin(t_mini *mini);
int		redir(t_mini *mini);
int		question_mark(t_mini *mini, size_t j, char *tmp);
int		check_char(char ch);
void	dollar_quotes(int *flag, char c);
int		ft_quotes_arg(t_pars *pars);
int		ft_quotes_red(t_red *red);

#endif
