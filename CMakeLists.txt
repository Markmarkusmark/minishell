cmake_minimum_required(VERSION 3.19)
project(minishell C)

set(CMAKE_C_STANDARD 11)

include_directories(get_next_line)
include_directories(include)
include_directories(libft)
include_directories(srcs)

add_executable(minishell
        get_next_line/get_next_line.c
        get_next_line/get_next_line.h
        get_next_line/get_next_line_utils.c
        include/minishell.h
        libft/ft_atoi.c
        libft/ft_bzero.c
        libft/ft_calloc.c
        libft/ft_isalnum.c
        libft/ft_isalpha.c
        libft/ft_isascii.c
        libft/ft_isdigit.c
        libft/ft_isprint.c
        libft/ft_itoa.c
        libft/ft_lstadd_back.c
        libft/ft_lstadd_front.c
        libft/ft_lstclear.c
        libft/ft_lstdelone.c
        libft/ft_lstiter.c
        libft/ft_lstlast.c
        libft/ft_lstmap.c
        libft/ft_lstnew.c
        libft/ft_lstsize.c
        libft/ft_memccpy.c
        libft/ft_memchr.c
        libft/ft_memcmp.c
        libft/ft_memcpy.c
        libft/ft_memmove.c
        libft/ft_memset.c
        libft/ft_putchar_fd.c
        libft/ft_putendl_fd.c
        libft/ft_putnbr_fd.c
        libft/ft_putstr_fd.c
        libft/ft_split.c
        libft/ft_strchr.c
        libft/ft_strdup.c
        libft/ft_strjoin.c
        libft/ft_strlcat.c
        libft/ft_strlcpy.c
        libft/ft_strlen.c
        libft/ft_strmapi.c
        libft/ft_strncmp.c
        libft/ft_strnstr.c
        libft/ft_strrchr.c
        libft/ft_strtrim.c
        libft/ft_substr.c
        libft/ft_tolower.c
        libft/ft_toupper.c
        libft/libft.h
        srcs/minishell.c
        srcs/syntax.c
        srcs/utils.c
        srcs/parser.c
        srcs/preparser.c
        srcs/parse_env.c
        srcs/env_list.c
        srcs/command.c
        srcs/builtin.c
        srcs/minishell_process.c
        srcs/redir.c
        srcs/execute.c
        srcs/echo.c
        srcs/cd.c
        )
add_definitions("-L /Users/mryan/.brew/opt/readline/lib")
add_definitions("-I /Users/mryan/.brew/opt/readline/include")
target_link_libraries(minishell readline)