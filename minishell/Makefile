# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tharland <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/21 15:17:30 by tharland          #+#    #+#              #
#    Updated: 2022/03/21 15:17:32 by tharland         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BUILTINS = 	echo.c pwd.c env.c cd.c export.c unset.c exit.c print_export.c
LIBFT    = 	-L libft -lft
TOOLS	 = 	get_env.c get_path.c init.c ft_strndup.c ft_findchr.c
FT_CLEAN = 	clean.c
PARSER	 = 	parser.c split_line.c redir.c dollar.c dest.c quotes.c sub_split_line.c quotes_utils.c dollar_utils.c
EXECUTOR = 	executor.c executor_utils.c redirect.c builtin.c
ERROR	 =	error.c
SRCS     =	$(addprefix builtins/, $(BUILTINS)) \
			$(addprefix tools/, $(TOOLS)) \
			$(addprefix parser/, $(PARSER)) \
			$(addprefix clean/, $(FT_CLEAN)) \
			$(addprefix executor/, $(EXECUTOR)) \
			$(addprefix error/, $(ERROR)) \
			main.c
OBJS     = 	$(SRCS:.c=.o)
NAME     = 	minishell
CC	     = 	gcc
FLAGS 	 =  -L/Users/$(USER)/.brew/Cellar/readline/8.1.2/lib/ -I/Users/$(USER)/.brew/Cellar/readline/8.1.2/include
CFLAGS   = 	-Wall -Wextra -Werror #-fsanitize=address 

all:		$(NAME)

$(NAME):	$(OBJS) minishell.h Makefile
			@make -C libft/
			@make bonus -C libft/
			$(CC) $(CFLAGS) $(FLAGS) $(OBJS) $(LIBFT) -o $(NAME) -lreadline

clean:
			rm -rf $(OBJS) tools/heredoc.txt
			@make clean -C libft/

fclean:		clean
			rm -rf $(NAME)
			@make fclean -C libft/

re:			fclean all

.PHONY: clean
