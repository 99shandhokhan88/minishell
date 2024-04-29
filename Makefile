
SRCS	= main.c

SRCS	+= parser.c input_split.c input_split2.c parser_delegator.c parser_variable.c parser_redir.c

SRCS	+= utils.c parser2.c parser_redir2.c handle_basic.c parser_error.c parser_redir3.c

SRCS	+= echo.c pwd.c cd_utils.c cd.c exec.c exec_utils.c env.c

SRCS	+= export.c export_utils.c unset.c pipe.c signal.c exit.c

LIBFT	= libft/libft.a

OBJS	= $(SRCS:.c=.o)

NAME	= minishell

LIBFT	= libft/libft.a

CLANG	= gcc -g

FLAGS	= -Wall -Wextra -Werror

INCLUDE	= -L libft -lft -lreadline




all:	$(NAME)

.PHONY:	clean fclean re bonus bench bclean

$(NAME): $(OBJS)
	cd libft && $(MAKE)
	$(CLANG) $(FLAGS) -o $(NAME) $(OBJS) $(INCLUDE)

clean:
	rm -f $(OBJS) $(B_OBJS)
	cd libft && $(MAKE) clean

fclean: clean
	rm -f $(NAME) $(BONUS)
	cd libft && $(MAKE) fclean

re: fclean all

%.o: %.c
	$(CLANG) $(FLAGS) -c $<  -o $(<:.c=.o)
