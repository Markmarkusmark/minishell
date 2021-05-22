#ifndef MINISHELL_H
# define MMINISHELL_H

# include "../libft/libft.h"
# include "fcntl.h"

typedef	struct			s_lst_com
{
	char				*str;
	int					symbol;
	struct s_lst_com	*next;
}						t_lst_com;

typedef	struct			s_lst_str
{
	t_lst_com			*command;
};