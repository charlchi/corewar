# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmoller <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/18 13:23:13 by cmoller           #+#    #+#              #
#    Updated: 2018/09/12 15:09:30 by cmoller          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	corewar
#FLAGS =	-Wall -Wextra -Werror
CC = gcc
SRC = $(wildcard *.c) $(wildcard libft/*.c)
OBJ = $(SRC:.c=.o)

ifeq ($(OS),Windows_NT)
	LFLAGS = -lglut -lGL -lm
else
	UNAME_S = $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		LFLAGS = -lglut -lGL -lm
	endif
	ifeq ($(UNAME_S),Darwin)
		LFLAGS = -framework GLUT -framework OpenGL
	endif
endif

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
	
