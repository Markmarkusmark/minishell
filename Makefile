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
	srcs/builtin/echo.c \
	srcs/builtin/cd.c \
	srcs/builtin/pwd.c \
	srcs/builtin/env.c \
	srcs/builtin/unset.c \
	srcs/builtin/export.c \
	srcs/builtin/exit.c \
	srcs/builtin/builtin.c \
	srcs/command.c \
	srcs/execute.c \
	srcs/redir.c \
	srcs/utils.c \
	srcs/pipe.c

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS) $(LIBFT) $(HEADER)
	$(CC) -lreadline -ltermcap -L ~/.brew/opt/readline/lib \
	-I ~/.brew/opt/readline/include \
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
