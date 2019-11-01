# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmoller <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/18 13:23:13 by cmoller           #+#    #+#              #
#    Updated: 2019/10/15 16:45:41 by cmoller          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	asm
FLAGS =	-Wall -Wextra -Werror -O0 -ggdb3
CC = gcc
SRC = $(wildcard *.c) $(wildcard ../libft/*.c)
OBJ = $(SRC:.c=.o)

%.o:		%.c
			$(CC) $(FLAGS) -c $< -o $@

all: 		$(NAME)

$(NAME):	$(OBJ)
			$(CC) -O0 -ggdb3 $(OBJ) -o $(NAME) $(LFLAGS)

clean:
			/bin/rm -f $(NAME)

fclean: 	clean
			/bin/rm -f *.o
			/bin/rm -f ../libft/*.o

re: 		fclean all
	
