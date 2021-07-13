NAME = minishell

HEADER = ./include/

LIBFT = libft/libft.a

CC = gcc

CFLAGS = -Werror -Wall -Wextra -g -I $(HEADER) #-fsanitize=address

SRCS =	srcs/minishell.c \
	srcs/minishell_process.c \
	srcs/parser.c \
	srcs/preparser.c \
	srcs/parse_env.c \
	srcs/env_list.c \
	srcs/syntax.c \
	srcs/echo.c \
	srcs/cd.c \
	srcs/command.c \
	srcs/builtin.c \
	srcs/execute.c \
	srcs/redir.c \
	srcs/utils.c

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS) $(LIBFT) $(HEADER)
	$(CC) -lreadline -ltermcap -L /Users/mryan/.brew/opt/readline/lib \
	-I /Users/mryan/.brew/opt/readline/include \
		$(OBJS) -o $(NAME) $(LIBFT)

$(LIBFT) :
	make -C ./libft

clean :
	rm -rf $(OBJS)
	make clean -C ./libft

fclean : clean
	rm $(NAME)
	make fclean -C ./libft

re : fclean all
