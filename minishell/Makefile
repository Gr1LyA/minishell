BUILTINS = echo.c pwd.c env.c
LIBFT    = -L libft -lft
TOOLS	 = get_env.c get_path.c init.c ft_strndup.c ft_findchr.c
FT_CLEAN = clean.c
PARSER	 = parser.c split_line.c redir.c dollar.c dest.c quotes.c
EXECUTOR = executor.c
SRCS     = $(addprefix builtins/, $(BUILTINS)) $(addprefix tools/, $(TOOLS)) $(addprefix parser/, $(PARSER)) $(addprefix clean/, $(FT_CLEAN)) main.c $(addprefix executor/, $(EXECUTOR))
OBJS     = $(SRCS:.c=.o)
NAME     = minishell
CC	     = clang
CFLAGS   = -fsanitize=address -Wall -Wextra -Werror

.c.o:
			$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJS) minishell.h Makefile
			@make -C libft/
			@make bonus -C libft/
			$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)

clean:
			rm -rf $(OBJS)
			@make clean -C libft/

fclean:		clean
			rm -rf $(NAME)
			@make fclean -C libft/

re:			fclean all

.PHONY: clean