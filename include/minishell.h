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

typedef struct		s_msh
{
    t_list		    *env;
    t_list		    *cmd;
	char			*str; // my input string
	char            **env_args;

}					t_msh;


# endif