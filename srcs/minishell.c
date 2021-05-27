#include "../include/minishell.h"

char	*get_line(t_all *all)
{
	char	*str;

	str = NULL;
	get_next_line(0, &str);
	return (str);
}

//int		return_status(int err)
//{
//    if (err == 0)
//        ft_putstr_fd("syntax error near unexpected token |\n", 1);
//    if (err == 1)
//        ft_putstr_fd("syntax error near unexpected token ;\n", 1);
//    return (0);
//}

int		limit(t_all *all, int i)
{
    int j;

    j = 0;
    while (i >= 0 && all->str[i] != ';')
    {
        if (all->str[i] == '|' && all->str[i + 1] == '|' && j == 0)
            return (0);
        if (ft_isalnum(all->str[i]))
            j++;
        i--;
    }
    return (j == 0 ? 0 : 1);
}

int		ft_preparse(t_all *all)
{
    int		i;

    i = 0;
    while (all->str[i])
    {
        if ((all->str[i] == ';') && !limit(all, i - 1))
            //return (return_status(1));
            return (0);
        else if (all->str[i] == '|' && all->str[i + 1] && all->str[i + 1] == '|')
        {
            if (!limit(all, i - 1))
                //return (return_status(5));
                return (0);
            else
                i++;
        }
        else if ((all->str[i] == '|') && !limit(all, i - 1))
            //return (return_status(0));
            return (0);
        i++;
    }
    return (1);
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
	if (ft_preparse(all))

}