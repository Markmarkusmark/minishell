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

# define TAB " \t\b\r\v\f"

typedef struct		s_env
{
	char			*name;
	char 			*content;
	struct s_env	*next;
}					t_env;

typedef struct		s_all
{
	char 			**env;
	char			*str; // my input string
	char			**arr1;
	char			**arr2;

}					t_all;

void 	close_prog(t_all *all, char *err);
void	ft_copyenv(t_all *all, char **env);

# endif