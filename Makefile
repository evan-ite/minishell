# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/12 14:07:09 by evan-ite          #+#    #+#              #
#    Updated: 2024/05/16 12:14:03 by evan-ite         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Werror -Wextra -g
RL_FLAGS = -lreadline -lncurses

LIBFT = src/libft/libft.a

SRC = src/main.c src/error.c src/free.c src/parse/parse.c src/parse/token.c \
	src/parse/node.c src/parse/parse_utils.c src/parse/quotes.c \
	src/parse/redirection.c src/parse/env_vars.c src/parse/check_syntax.c \
	src/parse/syntax_utils.c src/parse/token_utils.c \
	src/executing/execute.c src/executing/exec_utils.c src/executing/heredoc.c \
	src/executing/processes.c src/executing/path.c \
	src/builtins/cd.c src/builtins/echo.c src/builtins/env.c src/builtins/export.c \
	src/builtins/pwd.c src/builtins/unset.c src/builtins/exit.c \
	src/builtins/export_utils.c src/executing/files.c src/signals.c

OBJ := $(SRC:.c=.o)

all: libft $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(RL_FLAGS)

libft:
	$(MAKE) -C src/libft;

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f $(OBJ)
	$(MAKE) -C src/libft clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C src/libft fclean

re: fclean all

.PHONY: all clean fclean re libft
