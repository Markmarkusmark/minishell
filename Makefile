NAME = minishell

HEADER = ./include/

LIBFT = libft/libft.a

CC = gcc

CFLAGS = -Werror -Wall -Wextra -g -I $(HEADER) #-fsanitize=address

SRCS =	srcs/main/minishell.c \
	srcs/main/command.c \
	srcs/main/execute.c \
	srcs/main/execute_utils.c \
	srcs/main/redir.c \
	srcs/main/redir_utils.c \
	srcs/main/redir_utils_2.c \
	srcs/main/pipe.c \
	srcs/parse/parser.c \
	srcs/parse/parser_utils.c \
	srcs/parse/parser_utils2.c \
	srcs/parse/parser_utils3.c \
	srcs/parse/preparser.c \
	srcs/parse/parse_env.c \
	srcs/parse/parse_env_utils.c \
	srcs/parse/env_list.c \
	srcs/parse/syntax.c \
	srcs/builtin/echo.c \
	srcs/builtin/cd.c \
	srcs/builtin/pwd.c \
	srcs/builtin/env.c \
	srcs/builtin/unset.c \
	srcs/builtin/export.c \
	srcs/builtin/exit.c \
	srcs/builtin/builtin.c \
	srcs/utils.c \
	srcs/utils_2.c \
	srcs/utils_3.c \

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
