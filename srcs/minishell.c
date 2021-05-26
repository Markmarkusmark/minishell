#include "../include/minishell.h"

char	*get_line(t_all *all)
{
	char	*str;

	str = NULL;
	get_next_line(0, &str);
	return (str);
}

int		main(int argc, char **argv, char **env)
{
	t_all	*all;

	all = (t_all *)malloc(sizeof(t_all));
	if (!all)
		close_prog(all, "error memory");
	ft_bzero(all, sizeof(t_all));
	ft_copyenv(all, env);
	all->str = get_line(all);
}