# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/12 14:07:09 by evan-ite          #+#    #+#              #
#    Updated: 2024/04/17 17:12:16 by evan-ite         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Werror -Wextra -g
RL_FLAGS = -lreadline -lncurses

LIBFT = libft/libft.a

SRC = main.c error.c free.c parse/parse.c parse/token.c \
	parse/node.c parse/parse_utils.c parse/quotes.c \
	parse/redirection.c parse/env_vars.c parse/check_syntax.c \
	executing/execute.c executing/exec_utils.c \
	executing/processes.c executing/path.c \
	builtins/cd.c builtins/echo.c builtins/env.c builtins/export.c \
	builtins/pwd.c builtins/unset.c builtins/exit.c

OBJ := $(SRC:.c=.o)

all: libft $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(RL_FLAGS)

libft:
	$(MAKE) -C libft;

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f $(OBJ)
	$(MAKE) -C libft clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re libft
