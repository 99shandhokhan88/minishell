# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vzashev <vzashev@student.42roma.it>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/05 17:00:35 by vzashev           #+#    #+#              #
#    Updated: 2024/05/02 22:26:41 by vzashev          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = my_action.c my_brain_utils.c my_brain.c my_cd_utils.c my_cd.c my_echo.c my_envv.c my_exec_utils.c my_exec.c my_exit.c my_expander.c my_export_utils.c my_export.c my_here_doc.c my_lexer_utils.c my_lexer.c my_main.c my_parser.c my_pwd.c my_reds_utils_1.c my_reds_utils_2.c my_reds.c my_unset.c pipes.c signals.c splitter.c utils_1.c utils_2.c utils_3.c utils_4.c utils_5.c

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

#valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=supp_readline.supp ./minishell
