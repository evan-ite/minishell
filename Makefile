# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrodenbu <mrodenbu@student.42berlin.d      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/31 13:10:57 by mrodenbu          #+#    #+#              #
#    Updated: 2024/01/31 13:15:20 by mrodenbu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC =	main.c

OBJ = $(SRC:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

RL_FLAGS = -lreadline -lncurses

LIBS = -Llibft -lft

all:		$(NAME)

$(NAME):	libft $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(RL_FLAGS) $(LIBS)

%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

libft:
	make -C libft

clean:
	make clean -C libft
	rm -f *.o

fclean:		clean
	make fclean -C libft
	rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re