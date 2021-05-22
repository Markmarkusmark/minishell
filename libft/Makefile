# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: legunshi <legunshi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/31 16:05:22 by legunshi          #+#    #+#              #
#    Updated: 2020/11/11 21:26:13 by legunshi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ft_memset.c \
		ft_bzero.c \
		ft_memcpy.c \
 		ft_memccpy.c \
		ft_memmove.c \
		ft_memchr.c \
 		ft_memcmp.c \
 		ft_strlen.c \
 		ft_strlcpy.c \
 		ft_strlcat.c \
 		ft_strchr.c \
	 	ft_strrchr.c \
		ft_strnstr.c \
		ft_strncmp.c \
		ft_atoi.c \
		ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_calloc.c \
		ft_strdup.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_itoa.c \
		ft_strmapi.c \
		ft_split.c

SRC_BONUS = ft_lstnew.c \
		ft_lstadd_front.c \
		ft_lstsize.c \
		ft_lstlast.c \
		ft_lstadd_back.c \
		ft_lstdelone.c \
		ft_lstclear.c \
		ft_lstiter.c \
		ft_lstmap.c 


OBJ = $(SRC:.c=.o)

OBJ_BONUS = $(SRC_BONUS:.c=.o) 

CC = gcc

FLAGS = -Werror -Wall -Wextra

RM = rm -f

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)

bonus: all $(OBJ_BONUS)
	ar rc $(NAME) $(OBJ_BONUS)

%.o:%.c libft.h
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) *.o

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean all re bonus