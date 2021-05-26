#include "../include/minishell.h"

void 	close_prog(t_all *all, char *err)
{
	ft_putstr_fd(err, 2);
	free(all);
	exit(0);
}