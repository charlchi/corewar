# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmoller <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/18 13:23:13 by cmoller           #+#    #+#              #
#    Updated: 2018/06/07 13:06:49 by cmoller          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
NAME =	libft.a
FLAGS =	-Wall -Wextra -Werror
CC =	gcc
OBJ =	ft_memalloc.o ft_putnbr_fd.o ft_strjoin.o ft_strrev.o \
		ft_memccpy.o ft_putstr.o ft_strlcat.o ft_strsplit.o \
		ft_atoi.o ft_memchr.o ft_putstr_fd.o ft_strlcpy.o ft_strstr.o \
		ft_bzero.o ft_memcmp.o ft_strcat.o ft_strlen.o ft_strsub.o \
		ft_isalnum.o ft_memcpy.o ft_strchr.o ft_strmap.o ft_strtrim.o \
		ft_isalpha.o ft_memdel.o ft_strclr.o ft_strmapi.o ft_strwordchr.o \
		ft_isascii.o ft_memmove.o ft_strcmp.o ft_strncat.o ft_strwordcnt.o \
		ft_isblank.o ft_memset.o ft_strcpy.o ft_strncmp.o ft_tolower.o \
		ft_isdigit.o ft_putchar.o ft_strdel.o ft_strncpy.o ft_toupper.o \
		ft_isprint.o ft_putchar_fd.o ft_strdup.o ft_strnequ.o \
		ft_issign.o ft_putendl.o ft_strequ.o ft_strnew.o \
		ft_isspace.o ft_putendl_fd.o ft_striter.o ft_strnstr.o \
		ft_itoa.o ft_putnbr.o ft_striteri.o ft_strrchr.o ft_countint.o \
		ft_lstadd.o ft_lstdel.o ft_lstdelone.o ft_lstiter.o ft_lstmap.o \
		ft_putbyte_fd.o ft_lstnew.o ft_iswhite.o ft_strstrfree.o \
		ft_strstrlen.o ft_lstappend.o
FILES = ft_memalloc.c ft_putnbr_fd.c ft_strjoin.c ft_strrev.c \
		ft_memccpy.c ft_putstr.c ft_strlcat.c ft_strsplit.c \
		ft_atoi.c ft_memchr.c ft_putstr_fd.c ft_strlcpy.c ft_strstr.c \
		ft_bzero.c ft_memcmp.c ft_strcat.c ft_strlen.c ft_strsub.c \
		ft_isalnum.c ft_memcpy.c ft_strchr.c ft_strmap.c ft_strtrim.c \
		ft_isalpha.c ft_memdel.c ft_strclr.c ft_strmapi.c ft_strwordchr.c \
		ft_isascii.c ft_memmove.c ft_strcmp.c ft_strncat.c ft_strwordcnt.c \
		ft_isblank.c ft_memset.c ft_strcpy.c ft_strncmp.c ft_tolower.c \
		ft_isdigit.c ft_putchar.c ft_strdel.c ft_strncpy.c ft_toupper.c \
		ft_isprint.c ft_putchar_fd.c ft_strdup.c ft_strnequ.c \
		ft_issign.c ft_putendl.c ft_strequ.c ft_strnew.c \
		ft_isspace.c ft_putendl_fd.c ft_striter.c ft_strnstr.c \
		ft_itoa.c ft_putnbr.c ft_striteri.c ft_strrchr.c ft_countint.c \
		ft_lstadd.c ft_lstdel.c ft_lstdelone.c ft_lstiter.c ft_lstmap.c \
		ft_putbyte_fd.c ft_lstnew.c ft_iswhite.c ft_strstrfree.c \
		ft_strstrlen.c ft_lstappend.c

all: 		$(NAME)

$(OBJ):
			$(CC) $(FLAGS) -c $(FILES)

$(NAME):	$(OBJ)
			ar rc $(NAME) $(OBJ)
			ranlib $(NAME)

clean:
			/bin/rm -f *.o

fclean: 	clean
			/bin/rm -f $(NAME)

re: 		fclean all

so: 		$(OBJ)
			gcc -g -fPIC -Wall -Werror -Wextra -pedantic *.c -shared -o libft.so
	
