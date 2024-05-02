
SRCS = action.c expander.c lexer_utils.c lexer.c main.c my_brain_utils.c my_brain.c my_cd_utils.c my_cd.c my_echo.c my_envv.c my_exec_utils.c my_exec.c my_exit.c my_export_utils.c my_export.c my_pwd.c my_unset.c parser_redir2.c parser.c pipes.c redirections.c signals.c splitter.c utils.c

CC = gcc

CFLAGS = -Wall -Werror -Wextra -g

LDFLAGS = -lreadline

OBJS = $(SRCS:.c=.o)

EXEC = minishell

.PHONY: all clean fclean re

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(EXEC)

re: fclean all
