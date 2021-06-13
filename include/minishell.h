#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"
# include "fcntl.h"
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

# define MINISHELL_LOOP 1

typedef struct      s_env
{
    char            *key;
    char            *val;
}                   t_env;

typedef struct		s_line_symbol
{
	char			c;
	int 			flag;
}					t_line_symbol;

typedef struct      s_cmd
{
	char            *cmd;
	char            **args_str;
	char 			separ;
	int 			n_args;
	int 			n_redir;
}                   t_cmd;

typedef struct		s_msh
{
    t_list		    *env;
    t_list		    *cmd;
    t_line_symbol	*line;
	char			*str; // my input string
	char            **env_args;
	char 			*val_in_dlr;   // in this field environment after $
	int 			return_code;
	int 			fd_0;
	int 			fd_1;
}					t_msh;

# endif