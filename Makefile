# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmoller <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/18 13:23:13 by cmoller           #+#    #+#              #
#    Updated: 2018/09/25 12:57:47 by cmoller          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	corewar
FLAGS =	-Wall -Wextra -Werror
CC = gcc
SRC = $(wildcard *.c) $(wildcard libft/*.c)
OBJ = $(SRC:.c=.o)
LFLAGS = -lncurses

%.o:		%.c
			$(CC) $(FLAGS) -c $< -o $@

all: 		$(NAME)

$(NAME):	$(OBJ)
			$(CC) $(OBJ) -o $(NAME) $(LFLAGS)

clean:
			/bin/rm -f $(NAME)

fclean: 	clean
			/bin/rm -f *.o
			/bin/rm -f libft/*.o

re: 		fclean all
	
